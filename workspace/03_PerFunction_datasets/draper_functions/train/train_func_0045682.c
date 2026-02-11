setting_infiniband_details (NMSettingInfiniband *s_infiniband, NmCli *nmc)
{
	const GByteArray *mac;
	char *mtu_str, *mac_str = NULL;
	guint32 mode_flag = (nmc->print_output == NMC_PRINT_PRETTY) ? NMC_PF_FLAG_PRETTY : (nmc->print_output == NMC_PRINT_TERSE) ? NMC_PF_FLAG_TERSE : 0;
	guint32 multiline_flag = nmc->multiline_output ? NMC_PF_FLAG_MULTILINE : 0;
	guint32 escape_flag = nmc->escape_values ? NMC_PF_FLAG_ESCAPE : 0;

	g_return_val_if_fail (NM_IS_SETTING_INFINIBAND (s_infiniband), FALSE);

	nmc->allowed_fields = nmc_fields_setting_infiniband;
	nmc->print_fields.indices = parse_output_fields (NMC_FIELDS_SETTING_INFINIBAND_ALL, nmc->allowed_fields, NULL);
	nmc->print_fields.flags = multiline_flag | mode_flag | escape_flag | NMC_PF_FLAG_FIELD_NAMES;
	print_fields (nmc->print_fields, nmc->allowed_fields);

	mac = nm_setting_infiniband_get_mac_address (s_infiniband);
	if (mac)
		mac_str = nm_utils_hwaddr_ntoa (mac->data, ARPHRD_INFINIBAND);
	mtu_str = g_strdup_printf ("%d", nm_setting_infiniband_get_mtu (s_infiniband));

	nmc->allowed_fields[0].value = NM_SETTING_INFINIBAND_SETTING_NAME;
	nmc->allowed_fields[1].value = mac_str;
	nmc->allowed_fields[2].value = strcmp (mtu_str, "0") ? mtu_str : _("auto");
	nmc->allowed_fields[3].value = nm_setting_infiniband_get_transport_mode (s_infiniband);

	nmc->print_fields.flags = multiline_flag | mode_flag | escape_flag | NMC_PF_FLAG_SECTION_PREFIX;
	print_fields (nmc->print_fields, nmc->allowed_fields);

	g_free (mac_str);
	g_free (mtu_str);

	return TRUE;
}
