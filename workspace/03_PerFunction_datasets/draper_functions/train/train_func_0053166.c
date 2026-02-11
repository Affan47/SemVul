mthca_tavor_write_mtt_seg(struct mthca_dev *dev,
				      struct mthca_mtt *mtt, int start_index,
				      u64 *buffer_list, int list_len)
{
	u64 __iomem *mtts;
	int i;

	mtts = dev->mr_table.tavor_fmr.mtt_base + mtt->first_seg * dev->limits.mtt_seg_size +
		start_index * sizeof (u64);
	for (i = 0; i < list_len; ++i)
		mthca_write64_raw(cpu_to_be64(buffer_list[i] | MTHCA_MTT_FLAG_PRESENT),
				  mtts + i);
}
