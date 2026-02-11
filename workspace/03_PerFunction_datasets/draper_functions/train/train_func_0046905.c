pg_convert(PG_FUNCTION_ARGS)
{
	bytea	   *string = PG_GETARG_BYTEA_P(0);
	char	   *src_encoding_name = NameStr(*PG_GETARG_NAME(1));
	int			src_encoding = pg_char_to_encoding(src_encoding_name);
	char	   *dest_encoding_name = NameStr(*PG_GETARG_NAME(2));
	int			dest_encoding = pg_char_to_encoding(dest_encoding_name);
	unsigned char *result;
	bytea	   *retval;
	unsigned char *str;
	int			len;

	if (src_encoding < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid source encoding name \"%s\"",
						src_encoding_name)));
	if (dest_encoding < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid destination encoding name \"%s\"",
						dest_encoding_name)));


	len = VARSIZE(string) - VARHDRSZ;
	pg_verify_mbstr(src_encoding, VARDATA(string), len, false);
	str = palloc(len + 1);
	memcpy(str, VARDATA(string), len);
	*(str + len) = '\0';

	result = pg_do_encoding_conversion(str, len, src_encoding, dest_encoding);
	if (result == NULL)
		elog(ERROR, "encoding conversion failed");


	len = strlen((char *) result) + VARHDRSZ;
	retval = palloc(len);
	SET_VARSIZE(retval, len);
	memcpy(VARDATA(retval), result, len - VARHDRSZ);

	if (result != str)
		pfree(result);
	pfree(str);


	PG_FREE_IF_COPY(string, 0);

	PG_RETURN_BYTEA_P(retval);
}
