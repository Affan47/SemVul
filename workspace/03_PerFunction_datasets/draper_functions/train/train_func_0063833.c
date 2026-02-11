php_native_search_download_cmd(PHP_VALUE_NODE *)
{
	PHP_SCOPE_ITEM *si = get_scope_item(g_current_scope, "__param_0");
	if ( !si || (si->var->value.type != PHP_VAL_STRING)) {
		php_report_error(PHP_ERROR, "Invalid or missing argument 1 (file hash)");
		return;
	}
	char *str_hash = si->var->value.str_val;

	si = get_scope_item(g_current_scope, "__param_1");
	if ( !si || (si->var->value.type != PHP_VAL_STRING)) {
		php_report_error(PHP_ERROR, "Invalid or missing argument 2 (category)");
		return;
	}

	cast_value_dnum(&si->var->value);
	int cat = si->var->value.int_val;

	CPhPLibContext::g_curr_context->WebServer()->Send_DownloadSearchFile_Cmd(
		wxString(char2unicode(str_hash)), cat);
}
