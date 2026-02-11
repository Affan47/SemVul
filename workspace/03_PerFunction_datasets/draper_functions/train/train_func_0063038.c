ms_lib_set_logicalpair(struct us_data *us, u16 logblk, u16 phyblk)
{
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	if ((logblk >= info->MS_Lib.NumberOfLogBlock) || (phyblk >= info->MS_Lib.NumberOfPhyBlock))
		return (u32)-1;

	info->MS_Lib.Phy2LogMap[phyblk] = logblk;
	info->MS_Lib.Log2PhyMap[logblk] = phyblk;

	return 0;
}
