tda9874a_checkit(struct CHIPSTATE *chip)
{
	struct v4l2_subdev *sd = &chip->sd;
	int dic,sic;

	if(-1 == (dic = chip_read2(chip,TDA9874A_DIC)))
		return 0;
	if(-1 == (sic = chip_read2(chip,TDA9874A_SIC)))
		return 0;

	v4l2_dbg(1, debug, sd, "tda9874a_checkit(): DIC=0x%X, SIC=0x%X.\n", dic, sic);

	if((dic == 0x11)||(dic == 0x07)) {
		v4l2_info(sd, "found tda9874%s.\n", (dic == 0x11) ? "a" : "h");
		tda9874a_dic = dic;
		return 1;
	}
	return 0;
}
