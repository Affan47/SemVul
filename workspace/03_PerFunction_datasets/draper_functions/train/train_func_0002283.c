x2sys_get_data_path (char *track_path, char *track, char *suffix)
{
	int id;
	GMT_LONG add_suffix = FALSE;
	char geo_path[BUFSIZ], dotsuffix[GMT_TEXT_LEN];

	if (track[0] == '/' || track[1] == ':') {
		strcpy(track_path, track);
		return (0);
	}


	sprintf (dotsuffix, ".%s", suffix);
	add_suffix = strncmp (&track[strlen(track)-strlen(dotsuffix)], dotsuffix, strlen(dotsuffix));


	if (add_suffix)
		sprintf (geo_path, "%s.%s", track, suffix);
	else
		strcpy (geo_path, track);
	if (!access(geo_path, R_OK)) {
		strcpy(track_path, geo_path);
		return (0);
	}


	for (id = 0; id < n_x2sys_paths; id++) {
		if (add_suffix)
			sprintf (geo_path, "%s/%s.%s", x2sys_datadir[id], track, suffix);
		else
			sprintf (geo_path, "%s/%s", x2sys_datadir[id], track);
		if (!access (geo_path, R_OK)) {
			strcpy (track_path, geo_path);
			return (0);
		}
	}
	return(1);
}
