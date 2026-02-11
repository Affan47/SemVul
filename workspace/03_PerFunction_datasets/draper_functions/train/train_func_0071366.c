setting_bridge_port_details (NMSettingBridgePort *s_bridge_port, NmCli *nmc)
{
	guint32 mode_flag = (nmc->print_output == NMC_PRINT_PRETTY) ? NMC_PF_FLAG_PRETTY : (nmc->print_output == NMC_PRINT_TERSE) ? NMC_PF_FLAG_TERSE : 0;
	guint32 multiline_flag = nmc->multiline_output ? NMC_PF_FLAG_MULTILINE : 0;
	guint32 escape_flag = nmc->escape_values ? NMC_PF_FLAG_ESCAPE : 0;

	g_return_val_if_fail (NM_IS_SETTING_BRIDGE_PORT (s_bridge_port), FALSE);

	nmc->allowed_fields = nmc_fields_setting_bridge_port;
	nmc->print_fields.indices = parse_output_fields (NMC_FIELDS_SETTING_BRIDGE_PORT_ALL, nmc->allowed_fields, NULL);
	nmc->print_fields.flags = multiline_flag | mode_flag | escape_flag | NMC_PF_FLAG_FIELD_NAMES;
	print_fields (nmc->print_fields, nmc->allowed_fields);

	nmc->allowed_fields[0].value = NM_SETTING_BRIDGE_PORT_SETTING_NAME;
	nmc->allowed_fields[1].value = g_strdup_printf ("%u", nm_setting_bridge_port_get_priority (s_bridge_port));
	nmc->allowed_fields[2].value = g_strdup_printf ("%u", nm_setting_bridge_port_get_path_cost (s_bridge_port));
	nmc->allowed_fields[3].value = nm_setting_bridge_port_get_hairpin_mode (s_bridge_port) ? _("yes") : _("no");

	nmc->print_fields.flags = multiline_flag | mode_flag | escape_flag | NMC_PF_FLAG_SECTION_PREFIX;
	print_fields (nmc->print_fields, nmc->allowed_fields);

	g_free ((char*) nmc->allowed_fields[1].value);
	g_free ((char*) nmc->allowed_fields[2].value);

	return TRUE;
}
