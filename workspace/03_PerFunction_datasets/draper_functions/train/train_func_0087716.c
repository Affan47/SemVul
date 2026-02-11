handle_get_items_response_cb (EwsAsyncData *async_data, ESoapParameter *param)
{
	ESoapParameter *subparam;
	GError *error = NULL;

	subparam = e_soap_parameter_get_first_child (param);

	while (subparam != NULL) {
		const gchar *name = (const gchar *) subparam->name;

		if (g_str_has_suffix (name, "ResponseMessage")) {
			ews_get_response_status (subparam, &error);
			ews_handle_items_param (subparam, async_data, error);
		} else {
			g_warning (
				"%s: Unexpected element <%s>",
				G_STRFUNC, name);
		}


		if (error != NULL)
			g_clear_error (&error);

		subparam = e_soap_parameter_get_next_child (subparam);
	}
}
