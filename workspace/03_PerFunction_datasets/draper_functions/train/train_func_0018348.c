diskdump_get_osrelease(void)
{
	char *string;

	if ((string = vmcoreinfo_read_string("OSRELEASE"))) {
		fprintf(fp, "%s\n", string);
		free(string);
	}
	else
		pc->flags2 &= ~GET_OSRELEASE;
}
