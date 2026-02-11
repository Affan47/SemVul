print_config (cli_infos_t *infos, const gchar *confname)
{
	xmmsc_result_t *res;
	const gchar *confval;
	xmmsv_t *val;

	if (confname == NULL) {
		res = xmmsc_config_list_values (infos->sync);
		xmmsc_result_wait (res);
		val = xmmsc_result_get_value (res);
		xmmsv_dict_foreach (val, print_config_entry, NULL);
	} else {
		res = xmmsc_config_get_value (infos->sync, confname);
		xmmsc_result_wait (res);
		val = xmmsc_result_get_value (res);
		xmmsv_get_string (val, &confval);
		print_config_entry (confname, val, NULL);
	}

	cli_infos_loop_resume (infos);

	xmmsc_result_unref (res);
}
