SetDatabaseEncoding(int encoding)
{
	if (!PG_VALID_BE_ENCODING(encoding))
		elog(ERROR, "invalid database encoding: %d", encoding);

	DatabaseEncoding = &pg_enc2name_tbl[encoding];
	Assert(DatabaseEncoding->encoding == encoding);
}
