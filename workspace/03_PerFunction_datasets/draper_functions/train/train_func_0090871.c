pppoe_fill_defaults (NMSettingPPP *setting)
{
	if (!nm_setting_ppp_get_mtu (setting))
		g_object_set (setting, NM_SETTING_PPP_MTU, (guint32) 1492, NULL);

	if (!nm_setting_ppp_get_mru (setting))
		g_object_set (setting, NM_SETTING_PPP_MRU, (guint32) 1492, NULL);

	g_object_set (setting,
			    NM_SETTING_PPP_NOAUTH, TRUE,
			    NM_SETTING_PPP_NODEFLATE, TRUE,
			    NULL);


#if 0
	setting->noipdefault = TRUE;
	setting->default_asyncmap = TRUE;
	setting->defaultroute = TRUE;
	setting->hide_password = TRUE;
	setting->noaccomp = TRUE;
	setting->nopcomp = TRUE;
	setting->novj = TRUE;
	setting->novjccomp = TRUE;
#endif
}
