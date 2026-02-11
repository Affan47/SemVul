suspend_system(const char *suspend)
{
	FILE	*f = fopen(SYS_POWER_STATE_PATH, "w");

	if (!f) {
		warn(_("open failed: %s"), SYS_POWER_STATE_PATH);
		return;
	}

	if (!dryrun) {
		fprintf(f, "%s\n", suspend);
		fflush(f);
	}


	fclose(f);
}
