ican3_old_send_msg(struct ican3_dev *mod, struct ican3_msg *msg)
{
	unsigned int mbox, mbox_page;
	u8 locl, peer, xord;


	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	peer = ioread8(mod->dpm + MSYNC_PEER);
	locl = ioread8(mod->dpm + MSYNC_LOCL);
	xord = locl ^ peer;

	if ((xord & MSYNC_WB_MASK) == MSYNC_WB_MASK) {
		netdev_err(mod->ndev, "no mbox for writing\n");
		return -ENOMEM;
	}


	mbox = (xord & MSYNC_WB0) ? MSYNC_WB1 : MSYNC_WB0;


	mbox_page = (mbox == MSYNC_WB0) ? QUEUE_OLD_WB0 : QUEUE_OLD_WB1;
	ican3_set_page(mod, mbox_page);
	memcpy_toio(mod->dpm, msg, sizeof(*msg));

	locl ^= mbox;
	if (mbox == MSYNC_WB1)
		locl |= MSYNC_WBLW;

	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	iowrite8(locl, mod->dpm + MSYNC_LOCL);
	return 0;
}
