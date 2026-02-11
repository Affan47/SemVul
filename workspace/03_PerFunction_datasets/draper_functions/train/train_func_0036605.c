Colours_ReadConfig(char *option, char *ptr)
{
	if (COLOURS_NTSC_ReadConfig(option, ptr)) {
	}
	else if (COLOURS_PAL_ReadConfig(option, ptr)) {
	}
	else return FALSE;
	return TRUE;
}
