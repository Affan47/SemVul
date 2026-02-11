e_book_query_vcard_field_test (const gchar *field,
                               EBookQueryTest test,
                               const gchar *value)
{
	EBookQuery *ret = g_new0 (EBookQuery, 1);

	ret->type = E_BOOK_QUERY_TYPE_FIELD_TEST;
	ret->query.field_test.field_name = g_strdup (field);
	ret->query.field_test.test = test;
	ret->query.field_test.value = g_strdup (value);

	return ret;
}
