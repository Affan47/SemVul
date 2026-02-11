save_history(void)
{
    char *nanohist;


    if (!history_has_changed() || (searchbot->lineno == 1 &&
	replacebot->lineno == 1))
	return;

    nanohist = histfilename();

    if (nanohist != NULL) {
	FILE *hist = fopen(nanohist, "wb");

	if (hist == NULL)
	    rcfile_error(N_("Error writing %s: %s"), nanohist,
		strerror(errno));
	else {


	    chmod(nanohist, S_IRUSR | S_IWUSR);

	    if (!writehist(hist, searchage) || !writehist(hist,
		replaceage))
		rcfile_error(N_("Error writing %s: %s"), nanohist,
			strerror(errno));

	    fclose(hist);
	}

	free(nanohist);
    }
}
