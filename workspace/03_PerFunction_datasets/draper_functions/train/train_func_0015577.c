imapx_search_process_criteria (CamelSExp *sexp,
			       CamelFolderSearch *search,
			       CamelIMAPXServer *server,
			       const GString *criteria,
			       const gchar *from_function)
{
	CamelSExpResult *result;
	GPtrArray *uids = NULL;
	GError *error = NULL;

	uids = camel_imapx_server_uid_search (
		server, search->folder, criteria->str, NULL, &error);


	g_return_val_if_fail (
		((uids != NULL) && (error == NULL)) ||
		((uids == NULL) && (error != NULL)), NULL);


	if (error != NULL) {
		g_warning (
			"%s: (UID SEARCH %s): %s",
			from_function, criteria->str, error->message);
		uids = g_ptr_array_new ();
		g_error_free (error);
	}

	if (search->current != NULL) {
		result = camel_sexp_result_new (sexp, CAMEL_SEXP_RES_BOOL);
		result->value.boolean = (uids && uids->len > 0);
	} else {
		result = camel_sexp_result_new (sexp, CAMEL_SEXP_RES_ARRAY_PTR);
		result->value.ptrarray = g_ptr_array_ref (uids);
	}

	g_ptr_array_unref (uids);

	return result;
}
