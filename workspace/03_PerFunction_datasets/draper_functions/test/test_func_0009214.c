db_range_compare(sqlite3_context * context, int argc __attribute__ ((unused)), sqlite3_value ** argv)
{
	void *arg = sqlite3_user_data(context);
	struct db_query_arg *q = static_cast < struct db_query_arg *>(arg);
	assert(sqlite3_value_type(argv[0]) == SQLITE_TEXT);
	const char *text = reinterpret_cast < const char *>(sqlite3_value_text(argv[0]));
	bool retval;
	if (q->apol_range == NULL)
	{
		retval = query_str_compare(text, q->range, q->rerange, q->regex);
	}
	else
	{
		assert(q->policy != NULL);
		apol_mls_range_t *db_range = apol_mls_range_create_from_string(q->policy, text);
		int ret;
		ret = apol_mls_range_compare(q->policy, q->apol_range, db_range, q->rangeMatch);
		apol_mls_range_destroy(&db_range);
		retval = (ret > 0);
	}
	sqlite3_result_int(context, (retval ? 1 : 0));
}
