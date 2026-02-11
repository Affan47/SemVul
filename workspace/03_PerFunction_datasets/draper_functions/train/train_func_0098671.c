mthca_map_cmd(struct mthca_dev *dev, u16 op, struct mthca_icm *icm,
			 u64 virt)
{
	struct mthca_mailbox *mailbox;
	struct mthca_icm_iter iter;
	__be64 *pages;
	int lg;
	int nent = 0;
	int i;
	int err = 0;
	int ts = 0, tc = 0;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	memset(mailbox->buf, 0, MTHCA_MAILBOX_SIZE);
	pages = mailbox->buf;

	for (mthca_icm_first(icm, &iter);
	     !mthca_icm_last(&iter);
	     mthca_icm_next(&iter)) {


		lg = ffs(mthca_icm_addr(&iter) | mthca_icm_size(&iter)) - 1;
		if (lg < MTHCA_ICM_PAGE_SHIFT) {
			mthca_warn(dev, "Got FW area not aligned to %d (%llx/%lx).\n",
				   MTHCA_ICM_PAGE_SIZE,
				   (unsigned long long) mthca_icm_addr(&iter),
				   mthca_icm_size(&iter));
			err = -EINVAL;
			goto out;
		}
		for (i = 0; i < mthca_icm_size(&iter) >> lg; ++i) {
			if (virt != -1) {
				pages[nent * 2] = cpu_to_be64(virt);
				virt += 1 << lg;
			}

			pages[nent * 2 + 1] =
				cpu_to_be64((mthca_icm_addr(&iter) + (i << lg)) |
					    (lg - MTHCA_ICM_PAGE_SHIFT));
			ts += 1 << (lg - 10);
			++tc;

			if (++nent == MTHCA_MAILBOX_SIZE / 16) {
				err = mthca_cmd(dev, mailbox->dma, nent, 0, op,
						CMD_TIME_CLASS_B);
				if (err)
					goto out;
				nent = 0;
			}
		}
	}

	if (nent)
		err = mthca_cmd(dev, mailbox->dma, nent, 0, op,
				CMD_TIME_CLASS_B);

	switch (op) {
	case CMD_MAP_FA:
		mthca_dbg(dev, "Mapped %d chunks/%d KB for FW.\n", tc, ts);
		break;
	case CMD_MAP_ICM_AUX:
		mthca_dbg(dev, "Mapped %d chunks/%d KB for ICM aux.\n", tc, ts);
		break;
	case CMD_MAP_ICM:
		mthca_dbg(dev, "Mapped %d chunks/%d KB at %llx for ICM.\n",
			  tc, ts, (unsigned long long) virt - (ts << 10));
		break;
	}

out:
	mthca_free_mailbox(dev, mailbox);
	return err;
}
