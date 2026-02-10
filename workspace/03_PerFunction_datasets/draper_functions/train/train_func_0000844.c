cue_print (FILE *fp, Cd *cd)
{
	Cdtext *cdtext = cd_get_cdtext(cd);
	int i;
	Track *track = NULL;


	if (NULL != cd_get_catalog(cd)) {
		fprintf(fp, "CATALOG %s\n", cd_get_catalog(cd));
	}

	cue_print_cdtext(cdtext, fp, 0);


	for (i = 1; i <= cd_get_ntrack(cd); i++) {
		track = cd_get_track(cd, i);
		fprintf(fp, "\n");
		cue_print_track(fp, track, i);
	}
}
