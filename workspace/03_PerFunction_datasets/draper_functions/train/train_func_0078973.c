pg_read_file_all(PG_FUNCTION_ARGS)
{
	text	   *filename_t = PG_GETARG_TEXT_P(0);
	char	   *filename;

	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 (errmsg("must be superuser to read files"))));

	filename = convert_and_check_filename(filename_t);

	PG_RETURN_TEXT_P(read_text_file(filename, 0, -1));
}
