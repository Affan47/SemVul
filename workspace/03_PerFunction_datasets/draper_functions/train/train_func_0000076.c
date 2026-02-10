fmt_setup(void)
{
	if  (!formatstring  &&  !(formatstring = html_inistr("format", (char *) 0)))
		formatstring = sdefaultfmt;
}
