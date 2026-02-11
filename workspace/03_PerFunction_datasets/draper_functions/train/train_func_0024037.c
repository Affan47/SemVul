gnumeric_fopen_error_info (const char *file_name, const char *mode, GOErrorInfo **ret_error)
{
	FILE *f;

	g_return_val_if_fail (file_name != NULL, NULL);
	g_return_val_if_fail (mode != NULL, NULL);
	g_return_val_if_fail (ret_error != NULL, NULL);

	*ret_error = NULL;
	f = g_fopen (file_name, mode);
	if (f == NULL) {
		if (strchr (mode, 'w') != NULL && strchr (mode, 'r') == NULL) {
			*ret_error = go_error_info_new_printf (
			             _("Error while opening file \"%s\" for writing."),
			             file_name);
		} else {
			*ret_error = go_error_info_new_printf (
			             _("Error while opening file \"%s\" for reading."),
			             file_name);
		}
		go_error_info_add_details (*ret_error, go_error_info_new_from_errno ());
	}

	return f;
}
