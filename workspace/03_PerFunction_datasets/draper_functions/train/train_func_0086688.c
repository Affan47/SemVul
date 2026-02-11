php_native_strlen(PHP_VALUE_NODE *result)
{
	PHP_SCOPE_ITEM *si = get_scope_item(g_current_scope, "__param_0");
	if ( si ) {
		PHP_VALUE_NODE *param = &si->var->value;
		cast_value_str(param);
		if ( result ) {
			cast_value_dnum(result);
			result->int_val = strlen(param->str_val);
		}
	} else {
		php_report_error(PHP_ERROR, "Invalid or missing argument");
	}
}
