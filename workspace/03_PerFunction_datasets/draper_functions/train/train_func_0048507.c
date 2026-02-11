mthca_MAP_EQ(struct mthca_dev *dev, u64 event_mask, int unmap,
		 int eq_num)
{
	mthca_dbg(dev, "%s mask %016llx for eqn %d\n",
		  unmap ? "Clearing" : "Setting",
		  (unsigned long long) event_mask, eq_num);
	return mthca_cmd(dev, event_mask, (unmap << 31) | eq_num,
			 0, CMD_MAP_EQ, CMD_TIME_CLASS_B);
}
