_e2_cd1_response_cb (GtkDialog *dialog, gint response,
	E2_SpecificConfDialogRuntime *rt)
{
	switch (response)
	{
		case GTK_RESPONSE_OK:

			(*rt->apply_function) ();

			_e2_cd1_cancel (rt, FALSE);
			e2_option_disable_config_checks ();

			e2_option_file_write (NULL);

			e2_fs_touch_config_dir ();
			e2_option_enable_config_checks ();
			break;
		case GTK_RESPONSE_APPLY:
			(*rt->apply_function) ();


			break;
		default:
			_e2_cd1_cancel (rt, TRUE);
			break;
	}
}
