dsp_pm_2(void)
{
	Uint32 dummy;


	if (((cur_inst >> 8) & 0xffff) == 0x2000) {
		return;
	}

	if (((cur_inst >> 8) & 0xffe0) == 0x2040) {
		dsp_calc_ea((cur_inst>>8) & BITMASK(5), &dummy);
		return;
	}

	if (((cur_inst >> 8) & 0xfc00) == 0x2000) {
		dsp_pm_2_2();
		return;
	}

	dsp_pm_3();
}
