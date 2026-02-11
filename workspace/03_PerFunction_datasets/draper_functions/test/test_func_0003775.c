fswc_savepid(fswebcam_config_t *config)
{
	FILE *fpid = fopen(config->pidfile, "wt");

	if(!fpid)
	{
		ERROR("Error saving PID to file '%s'",config->pidfile);
		ERROR("fopen: %s", strerror(errno));

		return(-1);
	}

	fprintf(fpid, "%i\n", getpid());
	fclose(fpid);

	return(0);
}
