MGD77_Read_Header_Sequence (FILE *fp, char *record, int seq)
{
	int got;

	if (seq == 1) {
		got = fgetc (fp);
		ungetc (got, fp);
		if (! (got == '4' || got == '1')) {
			fprintf (stderr, "MGD77_Read_Header: No header record present\n");
			return (MGD77_NO_HEADER_REC);
		}
	}
	if (fgets (record, MGD77_HEADER_LENGTH + 3, fp) == NULL) {
		fprintf (stderr, "MGD77_Read_Header: Failure to read header sequence %2.2d\n", seq);
		return (MGD77_ERROR_READ_HEADER_ASC);
	}
	GMT_chop (record);

	got = atoi (&record[78]);
	if (got != seq) {
		fprintf (stderr, "MGD77_Read_Header: Expected header sequence %2.2d says it is %2.2d\n", seq, got);
		return (MGD77_WRONG_HEADER_REC);
	}
	return (MGD77_NO_ERROR);
}
