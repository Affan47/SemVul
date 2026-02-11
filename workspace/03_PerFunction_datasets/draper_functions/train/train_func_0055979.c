bool_parse (const gchar* str) {
	gboolean result = FALSE;
	const gchar* _tmp0_ = NULL;
	g_return_val_if_fail (str != NULL, FALSE);
	_tmp0_ = str;
	if (g_strcmp0 (_tmp0_, "true") == 0) {
		result = TRUE;
		return result;
	} else {
		result = FALSE;
		return result;
	}
}
