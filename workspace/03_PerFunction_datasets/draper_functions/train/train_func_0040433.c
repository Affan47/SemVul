check_pst_table(struct powernow_k8_data *data, struct pst_s *pst,
		u8 maxvid)
{
	unsigned int j;
	u8 lastfid = 0xff;

	for (j = 0; j < data->numps; j++) {
		if (pst[j].vid > LEAST_VID) {
			pr_err(FW_BUG "vid %d invalid : 0x%x\n", j,
				pst[j].vid);
			return -EINVAL;
		}
		if (pst[j].vid < data->rvo) {

			pr_err(FW_BUG "0 vid exceeded with pstate %d\n", j);
			return -ENODEV;
		}
		if (pst[j].vid < maxvid + data->rvo) {

			pr_err(FW_BUG "maxvid exceeded with pstate %d\n", j);
			return -ENODEV;
		}
		if (pst[j].fid > MAX_FID) {
			pr_err(FW_BUG "maxfid exceeded with pstate %d\n", j);
			return -ENODEV;
		}
		if (j && (pst[j].fid < HI_FID_TABLE_BOTTOM)) {

			pr_err(FW_BUG "two low fids - %d : 0x%x\n", j,
				pst[j].fid);
			return -EINVAL;
		}
		if (pst[j].fid < lastfid)
			lastfid = pst[j].fid;
	}
	if (lastfid & 1) {
		pr_err(FW_BUG "lastfid invalid\n");
		return -EINVAL;
	}
	if (lastfid > LO_FID_TABLE_TOP)
		pr_info(FW_BUG "first fid not from lo freq table\n");

	return 0;
}
