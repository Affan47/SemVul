test_setting_gsm_apn_underscore (void)
{
	NMSettingGsm *s_gsm;
	GError *error = NULL;
	gboolean success;

	s_gsm = (NMSettingGsm *) nm_setting_gsm_new ();
	g_assert (s_gsm);

	g_object_set (s_gsm, NM_SETTING_GSM_NUMBER, "*99#", NULL);


	g_object_set (s_gsm, NM_SETTING_GSM_APN, "foobar_baz", NULL);
	success = nm_setting_verify (NM_SETTING (s_gsm), NULL, &error);
	g_assert_no_error (error);
	g_assert (success == TRUE);
}
