phishy_map(int phishy,enum phish_status fallback)
{
	if(phishy&PHISHY_USERNAME_IN_URL)
		return CL_PHISH_CLOAKED_UIU;
	else if(phishy&PHISHY_NUMERIC_IP)
		return CL_PHISH_NUMERIC_IP;
	else
		return fallback;
}
