ds_show_message(const char *message)
{
	FILE *logfp;
	printf("%s\n", message);
	fflush(stdout);

	if ((logfp = get_logfp())) {
		fprintf(logfp, "%s\n", message);
		fclose(logfp);
	}

	return;
}
