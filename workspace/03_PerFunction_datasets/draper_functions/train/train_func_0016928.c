diskfile_iswriteprotect (struct uae_prefs *p, const TCHAR *fname, int *needwritefile, drive_type *drvtype)
{
#ifdef FSUAE
	write_log("diskfile_iswriteprotect fname=%s\n", fname);
#endif
	struct zfile *zf1, *zf2;
	bool wrprot1 = 0, wrprot2 = 1;
	uae_char buffer[25];

	*needwritefile = 0;
	*drvtype = DRV_35_DD;
	DISK_validate_filename (p, fname, 1, &wrprot1, NULL, &zf1);
	if (!zf1)
		return 1;
	if (zfile_iscompressed (zf1)) {
		wrprot1 = 1;
		*needwritefile = 1;
	}
	zf2 = getwritefile (p, fname, &wrprot2);
	zfile_fclose (zf2);
	zfile_fread (buffer, sizeof (char), 25, zf1);
	zfile_fclose (zf1);
	if (strncmp ((uae_char*) buffer, "CAPS", 4) == 0) {
		*needwritefile = 1;
		return wrprot2;
	}
	if (strncmp ((uae_char*) buffer, "Formatted Disk Image file", 25) == 0) {
		*needwritefile = 1;
		return wrprot2;
	}
	if (strncmp ((uae_char*) buffer, "UAE-1ADF", 8) == 0) {
		if (wrprot1)
			return wrprot2;
		return wrprot1;
	}
	if (strncmp ((uae_char*) buffer, "UAE--ADF", 8) == 0) {
		*needwritefile = 1;
		return wrprot2;
	}
	if (memcmp (exeheader, buffer, sizeof exeheader) == 0)
		return 0;
	if (wrprot1)
		return wrprot2;
	return wrprot1;
}
