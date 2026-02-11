md5_bytea(PG_FUNCTION_ARGS)
{
	bytea	   *in = PG_GETARG_BYTEA_P(0);
	size_t		len;
	char		hexsum[MD5_HASH_LEN + 1];
	text	   *result_text;

	len = VARSIZE(in) - VARHDRSZ;
	if (pg_md5_hash(VARDATA(in), len, hexsum) == false)
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));

	result_text = PG_STR_GET_TEXT(hexsum);
	PG_RETURN_TEXT_P(result_text);
}
