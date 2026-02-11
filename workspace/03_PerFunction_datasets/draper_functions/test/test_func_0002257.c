MGD77_Read_Header_Record_m77t (char *file, struct MGD77_CONTROL *F, struct MGD77_HEADER *H)
{
	char *MGD77_header, line[BUFSIZ], *not_used = NULL;
	int i, err, n_eols, c, n;

	n_eols = c = n = 0;


	memset ((void *)H, '\0', sizeof (struct MGD77_HEADER));

	while (fgets (line, BUFSIZ, F->fp)) H->n_records++;
	rewind (F->fp);
	H->n_records -= MGD77T_N_HEADER_RECORDS;

	not_used = fgets (line, BUFSIZ, F->fp);

	MGD77_header = (char *)GMT_memory (VNULL, (size_t)MGD77T_HEADER_LENGTH, sizeof (char), GMT_program);
	not_used = fgets (MGD77_header, BUFSIZ, F->fp);

	for (i = 0; i < 2; i++) H->mgd77[i] = (struct MGD77_HEADER_PARAMS *) GMT_memory (VNULL, (size_t)1, sizeof (struct MGD77_HEADER_PARAMS), GMT_program);

	if ((err = MGD77_Decode_Header_m77t (H->mgd77[MGD77_ORIG], MGD77_header))) return (err);
	GMT_free ((void *)MGD77_header);


	MGD77_set_plain_mgd77 (H, TRUE);
	if ((err = MGD77_Order_Columns (F, H))) return (err);

	return (MGD77_NO_ERROR);
}
