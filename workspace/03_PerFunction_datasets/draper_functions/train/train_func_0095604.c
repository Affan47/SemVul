xeon_ppd_bar4_split(struct intel_ntb_dev *ndev, u8 ppd)
{
	if (ppd & XEON_PPD_SPLIT_BAR_MASK) {
		dev_dbg(ndev_dev(ndev), "PPD %d split bar\n", ppd);
		return 1;
	}
	return 0;
}
