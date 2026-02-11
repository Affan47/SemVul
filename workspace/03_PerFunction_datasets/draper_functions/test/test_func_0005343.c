MGD77_Write_Data_Record (struct MGD77_CONTROL *F, struct MGD77_HEADER *H, double dvals[], char *tvals[])
{
	int i, k, error;
	struct MGD77_DATA_RECORD MGD77Record;

	switch (F->format) {
		case MGD77_FORMAT_M77:
			MGD77Record.time = dvals[0];
			for (i = 1; i < MGD77_N_NUMBER_FIELDS; i++) MGD77Record.number[MGD77_pos[i]] = dvals[i];
			for (k = 0; k < MGD77_N_STRING_FIELDS; k++) strcpy (MGD77Record.word[k], tvals[k]);
			error = MGD77_Write_Data_Record_m77 (F, &MGD77Record);
			break;
		case MGD77_FORMAT_CDF:
			error = MGD77_Write_Data_Record_cdf (F, H, dvals, tvals);
			break;
		case MGD77_FORMAT_M7T:
			MGD77Record.time = dvals[0];
			for (i = 0; i < MGD77T_N_NUMBER_FIELDS; i++) MGD77Record.number[MGD77_pos[i]] = dvals[i];
			for (k = 0; k < MGD77_N_STRING_FIELDS; k++) strcpy (MGD77Record.word[k], tvals[k]);
			error = MGD77_Write_Data_Record_m77t (F, &MGD77Record);
			break;
		case MGD77_FORMAT_TBL:
			MGD77Record.time = dvals[0];
			for (i = 0; i < MGD77_N_NUMBER_FIELDS; i++) MGD77Record.number[MGD77_pos[i]] = dvals[i];
			for (k = 0; k < MGD77_N_STRING_FIELDS; k++) strcpy (MGD77Record.word[k], tvals[k]);
			error = MGD77_Write_Data_Record_txt (F, &MGD77Record);
			break;
		default:
			error = MGD77_UNKNOWN_FORMAT;
			break;
	}

	return (error);
}
