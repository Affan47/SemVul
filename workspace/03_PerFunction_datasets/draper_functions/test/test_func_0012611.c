mission_campaign_get_filenames(char *filename, char dest[][NAME_LENGTH], int *num)
{
	int	rval;


	if ((rval = setjmp(parse_abort)) != 0) {
		mprintf(("MISSIONCAMPAIGN: Unable to parse '%s'!  Error code = %i.\n", filename, rval));
		return rval;

	} else {
		Assert( strlen(filename) < MAX_FILENAME_LEN );
		read_file_text(filename);
		reset_parse();

		required_string("$Name:");
		advance_to_eoln(NULL);

		required_string( "$Type:" );
		advance_to_eoln(NULL);


		*num = 0;
		while ( skip_to_string("$Mission:") == 1 ) {
			stuff_string(dest[*num], F_NAME, NAME_LENGTH);
			(*num)++;
		}
	}

	return 0;
}
