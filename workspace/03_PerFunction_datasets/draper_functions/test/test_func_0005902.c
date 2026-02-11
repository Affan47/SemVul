dpm_reallocate_space (dbfd)
struct dpm_dbfd *dbfd;
{
	int bol = 1;
	int c;
	DBLISTPTR dblistptr;
	struct dpm_space_reserv dpm_spcmd;
	char func[21];
	struct dpm_put_filereq pfr_entry;
	struct stat64 statbuf;

	strcpy (func, "dpm_reallocate_space");
	dpmlogit (func, "Reallocating the space needed by reservespace requests\n");
	while ((c = dpm_list_spcmd_entry (dbfd, bol, &dpm_spcmd, 0, &dblistptr)) == 0) {
		bol = 0;
		dpm_updpoolfreespace (dpm_spcmd.poolname, -dpm_spcmd.u_space);
	}
	(void) dpm_list_spcmd_entry (dbfd, bol, &dpm_spcmd, 1, &dblistptr);
	if (c < 0)
		return (c);

	bol = 1;
	dpmlogit (func, "Reallocating the space needed by pending requests\n");
	while ((c = dpm_list_rr_puts (dbfd, bol, &pfr_entry, 0, &dblistptr)) == 0) {
		bol = 0;
		if (rfio_stat64 (pfr_entry.pfn, &statbuf) != 0)
			statbuf.st_size = 0;
		dpm_updfreespace (pfr_entry.pfn, statbuf.st_size -
		    pfr_entry.requested_size, pfr_entry.s_token, 0);
	}
	(void) dpm_list_rr_puts (dbfd, bol, &pfr_entry, 1, &dblistptr);
	return (c < 0 ? -1 : 0);
}
