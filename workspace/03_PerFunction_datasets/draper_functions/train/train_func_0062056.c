MGD77_Read_File (char *file, struct MGD77_CONTROL *F, struct MGD77_DATASET *S)
{
	int err = 0;

	switch (F->format) {
		case MGD77_FORMAT_M77:
		case MGD77_FORMAT_M7T:
		case MGD77_FORMAT_TBL:
			err = MGD77_Read_File_asc (file, F, S);
			break;
		case MGD77_FORMAT_CDF:
			err = MGD77_Read_File_cdf (file, F, S);
			break;
		default:
			fprintf (stderr, "%s: Bad format (%d)!\n", GMT_program, F->format);
			err = MGD77_UNKNOWN_FORMAT;
	}
	return (err);
}
