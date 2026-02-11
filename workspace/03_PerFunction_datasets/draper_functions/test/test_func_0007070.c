mthca_write_mtt(struct mthca_dev *dev, struct mthca_mtt *mtt,
		    int start_index, u64 *buffer_list, int list_len)
{
	int size = mthca_write_mtt_size(dev);
	int chunk;

	if (dev->mr_table.fmr_mtt_buddy != &dev->mr_table.mtt_buddy ||
	    !(dev->mthca_flags & MTHCA_FLAG_FMR))
		return __mthca_write_mtt(dev, mtt, start_index, buffer_list, list_len);

	while (list_len > 0) {
		chunk = min(size, list_len);
		if (mthca_is_memfree(dev))
			mthca_arbel_write_mtt_seg(dev, mtt, start_index,
						  buffer_list, chunk);
		else
			mthca_tavor_write_mtt_seg(dev, mtt, start_index,
						  buffer_list, chunk);

		list_len    -= chunk;
		start_index += chunk;
		buffer_list += chunk;
	}

	return 0;
}
