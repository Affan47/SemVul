__mthca_write_mtt(struct mthca_dev *dev, struct mthca_mtt *mtt,
			     int start_index, u64 *buffer_list, int list_len)
{
	struct mthca_mailbox *mailbox;
	__be64 *mtt_entry;
	int err = 0;
	int i;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	mtt_entry = mailbox->buf;

	while (list_len > 0) {
		mtt_entry[0] = cpu_to_be64(dev->mr_table.mtt_base +
					   mtt->first_seg * dev->limits.mtt_seg_size +
					   start_index * 8);
		mtt_entry[1] = 0;
		for (i = 0; i < list_len && i < MTHCA_MAILBOX_SIZE / 8 - 2; ++i)
			mtt_entry[i + 2] = cpu_to_be64(buffer_list[i] |
						       MTHCA_MTT_FLAG_PRESENT);


		if (i & 1)
			mtt_entry[i + 2] = 0;

		err = mthca_WRITE_MTT(dev, mailbox, (i + 1) & ~1);
		if (err) {
			mthca_warn(dev, "WRITE_MTT failed (%d)\n", err);
			goto out;
		}

		list_len    -= i;
		start_index += i;
		buffer_list += i;
	}

out:
	mthca_free_mailbox(dev, mailbox);
	return err;
}
