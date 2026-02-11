DoWriteReg(app)
bool	app;
{
	char	fnamebuf[FILESIZE];
	Mark	*mp = CurMark();
	File	*fp;


	(void) ask_file((char *)NULL, (char *)NULL, fnamebuf);

	if (!app) {
		filemunge(fnamebuf);
		chk_divergence((Buffer *)NULL, fnamebuf, "write-region");
#ifdef BACKUPFILES
		if (BkupOnWrite)
			file_backup(fnamebuf);
#endif
	}

	fp = open_file(fnamebuf, iobuff, app ? F_APPEND|F_TELLALL : F_WRITE|F_TELLALL, YES);
	putreg(fp, mp->m_line, mp->m_char, curline, curchar, YES);
	close_file(fp);
}
