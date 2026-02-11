ticket_write(const char *ticket_filename, struct chirp_ticket *ct)
{
	CHIRP_FILE *tf = cfs_fopen(ticket_filename, "w");
	if(!tf)
		return 0;

	char *str = chirp_ticket_tostring(ct);

	cfs_fprintf(tf, "%s", str);
	free(str);

	int result = cfs_ferror(tf);
	cfs_fclose(tf);
	if(result) {
		errno = EACCES;
		return -1;
	}
	return 0;
}
