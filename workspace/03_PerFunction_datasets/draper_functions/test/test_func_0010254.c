list_plugins (cli_infos_t *infos, xmmsc_result_t *res)
{
	const gchar *name, *desc, *err;
	xmmsv_t *val;

	val = xmmsc_result_get_value (res);

	if (!xmmsv_get_error (val, &err)) {
		xmmsv_list_iter_t *it;

		xmmsv_get_list_iter (val, &it);

		for (xmmsv_list_iter_first (it);
		     xmmsv_list_iter_valid (it);
		     xmmsv_list_iter_next (it)) {
			xmmsv_t *elem;

			xmmsv_list_iter_entry (it, &elem);
			xmmsv_dict_entry_get_string (elem, "shortname", &name);
			xmmsv_dict_entry_get_string (elem, "description", &desc);

			g_printf ("%s - %s\n", name, desc);
		}
	} else {
		g_printf (_("Server error: %s\n"), err);
	}

	xmmsc_result_unref (res);

	cli_infos_loop_resume (infos);
}
