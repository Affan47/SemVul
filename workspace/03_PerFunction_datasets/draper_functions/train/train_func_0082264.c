setting_cdma_details (NMSettingCdma *s_cdma, NmCli *nmc)
{
	char *pswd_flags;
	guint32 mode_flag = (nmc->print_output == NMC_PRINT_PRETTY) ? NMC_PF_FLAG_PRETTY : (nmc->print_output == NMC_PRINT_TERSE) ? NMC_PF_FLAG_TERSE : 0;
	guint32 multiline_flag = nmc->multiline_output ? NMC_PF_FLAG_MULTILINE : 0;
	guint32 escape_flag = nmc->escape_values ? NMC_PF_FLAG_ESCAPE : 0;

	g_return_val_if_fail (NM_IS_SETTING_CDMA (s_cdma), FALSE);

	nmc->allowed_fields = nmc_fields_setting_cdma;
	nmc->print_fields.indices = parse_output_fields (NMC_FIELDS_SETTING_CDMA_ALL, nmc->allowed_fields, NULL);
	nmc->print_fields.flags = multiline_flag | mode_flag | escape_flag | NMC_PF_FLAG_FIELD_NAMES;
	print_fields (nmc->print_fields, nmc->allowed_fields);

	pswd_flags = secret_flags_to_string (nm_setting_cdma_get_password_flags (s_cdma));

	nmc->allowed_fields[0].value = NM_SETTING_CDMA_SETTING_NAME;
	nmc->allowed_fields[1].value = nm_setting_cdma_get_number (s_cdma);
	nmc->allowed_fields[2].value = nm_setting_cdma_get_username (s_cdma);
	nmc->allowed_fields[3].value = nm_setting_cdma_get_password (s_cdma);
	nmc->allowed_fields[4].value = pswd_flags;

	nmc->print_fields.flags = multiline_flag | mode_flag | escape_flag | NMC_PF_FLAG_SECTION_PREFIX;
	print_fields (nmc->print_fields, nmc->allowed_fields);

	g_free (pswd_flags);

	return TRUE;
}
