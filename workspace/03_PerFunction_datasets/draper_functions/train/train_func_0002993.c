desc_free(TDS_DESC * desc)
{
	if (desc) {
		desc_free_records(desc);
		odbc_errs_reset(&desc->errs);
		free(desc);
	}
	return SQL_SUCCESS;
}
