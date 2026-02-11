click_single_db_show_messages (ClickSingleDB* self) {
	gboolean result = FALSE;
	const gchar* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = g_getenv ("TEST_QUIET");
	result = _tmp0_ == NULL;
	return result;
}
