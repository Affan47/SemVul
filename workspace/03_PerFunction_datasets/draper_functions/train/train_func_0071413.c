FScreenGetScreenArgument(char *scr_spec, fscreen_scr_spec_t default_screen)
{
	while (scr_spec && isspace(*scr_spec))
	{
		scr_spec++;
	}

	return FScreenParseScreenBit(scr_spec, default_screen);
}
