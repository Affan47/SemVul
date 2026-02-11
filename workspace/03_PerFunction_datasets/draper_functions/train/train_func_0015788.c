dump_country (gpointer key, gpointer value, gpointer user_data)
{
	GSList *miter, *citer;
	NMACountryInfo *country_info = value;

	g_print ("Country: %s (%s)\n",
	         country_info->country_code,
	         country_info->country_name);

	for (citer = country_info->providers; citer; citer = g_slist_next (citer)) {
		NMAMobileProvider *provider = citer->data;
		const gchar **mcc_mnc;
		const guint *sid;
		guint n;

		g_print ("	  Provider: %s (%s)\n", provider->name, (const char *) key);

		mcc_mnc = nma_mobile_provider_get_3gpp_mcc_mnc (provider);
		if (mcc_mnc) {
			for (n = 0; mcc_mnc[n]; n++)
				g_print ("		  MCC/MNC: %s\n", mcc_mnc[n]);
		}

		sid = nma_mobile_provider_get_cdma_sid (provider);
		if (sid) {
			for (n = 0; sid[n]; n++)
				g_print ("		  SID: %u\n", sid[n]);
		}

		for (miter = provider->methods; miter; miter = g_slist_next (miter)) {
			NMAMobileAccessMethod *method = miter->data;

			switch (method->family) {
			case NMA_MOBILE_FAMILY_CDMA:
				dump_cdma (method);
				break;
			case NMA_MOBILE_FAMILY_3GPP:
				dump_3gpp (method);
				break;
			default:
				break;
			}
			g_print ("\n");
		}
	}
}
