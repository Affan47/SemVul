mission_campaign_get_mission_list(char *filename, char **list, int max)
{
	int rval, i, num = 0;
	char name[MAX_FILENAME_LEN];

	filename = cf_add_ext(filename, FS_CAMPAIGN_FILE_EXT);


	if ((rval = setjmp(parse_abort)) != 0) {
		mprintf(("MISSIONCAMPAIGN: Unable to parse '%s'!  Error code = %i.\n", filename, rval));


		for (i=0; i<num; i++)
			vm_free(list[i]);

		num = -1;

	} else {
		read_file_text(filename);
		reset_parse();

		while (skip_to_string("$Mission:") > 0) {
			stuff_string(name, F_NAME, MAX_FILENAME_LEN);
			if (num < max)
				list[num++] = vm_strdup(name);
			else
				Warning(LOCATION, "Maximum number of missions exceeded (%d)!", max);
		}
	}

	return num;
}
