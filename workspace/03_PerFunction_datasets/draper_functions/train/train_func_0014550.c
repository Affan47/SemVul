sprintf_filesys_unit (TCHAR *buffer, int num)
{
	UnitInfo *uip = mountinfo.ui;

	if (uip[num].volname != 0)
		_stprintf (buffer, _T("(DH%d:) Filesystem, %s: %s %s"), num, uip[num].volname,
		uip[num].rootdir, uip[num].readonly ? "ro" : "");
	else
		_stprintf (buffer, _T("(DH%d:) Hardfile, \"%s\", size %d Mbytes"), num,
		uip[num].rootdir, (int)(uip[num].hf.virtsize / (1024 * 1024)));
	return 0;
}
