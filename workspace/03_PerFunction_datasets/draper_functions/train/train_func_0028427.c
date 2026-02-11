adsp2104_info(void *context, int regnum)
{
	switch( regnum )
    {
		case CPU_INFO_NAME: return "ADSP2104";
		case CPU_INFO_VERSION: return "1.0";
		case CPU_INFO_REG_LAYOUT: return (const char*)adsp2104_reg_layout;
		case CPU_INFO_WIN_LAYOUT: return (const char*)adsp2104_win_layout;
	}
	return adsp2100_info(context,regnum);
}
