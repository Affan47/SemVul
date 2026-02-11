get_hardfile_data (int nr)
{
	UnitInfo *uip = mountinfo.ui;
	if (nr < 0 || nr >= MAX_FILESYSTEM_UNITS || uip[nr].open == 0 || is_virtual (nr))
		return 0;
	return &uip[nr].hf;
}
