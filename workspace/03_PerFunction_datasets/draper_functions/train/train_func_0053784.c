hashtext(PG_FUNCTION_ARGS)
{
	text	   *key = PG_GETARG_TEXT_PP(0);
	Datum		result;


	result = hash_any((unsigned char *) VARDATA_ANY(key),
					  VARSIZE_ANY_EXHDR(key));


	PG_FREE_IF_COPY(key, 0);

	return result;
}
