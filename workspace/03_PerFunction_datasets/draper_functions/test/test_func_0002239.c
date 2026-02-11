_output_dell_system_info_idrac_info (ipmi_oem_state_data_t *state_data)
{
  uint8_t dhcp_or_static;
  char ip_address_buf[IPMI_OEM_STR_BUFLEN + 1];
  char idrac_firmware_version_buf[IPMI_OEM_STR_BUFLEN + 1];
  uint8_t idrac_type;
  char *dhcp_or_static_str;
  char *idrac_type_str;
  int rv = -1;
  int ret;

  assert (state_data);
  assert (state_data->prog_data->args->oem_options_count == 1);

  memset (ip_address_buf, '\0', IPMI_OEM_STR_BUFLEN + 1);
  memset (idrac_firmware_version_buf, '\0', IPMI_OEM_STR_BUFLEN + 1);

  if ((ret = _get_dell_system_info_idrac_info (state_data,
					       &dhcp_or_static,
					       ip_address_buf,
					       IPMI_OEM_STR_BUFLEN,
					       idrac_firmware_version_buf,
					       IPMI_OEM_STR_BUFLEN,
					       &idrac_type)) < 0)
    goto cleanup;

  if (!ret)
    {
      pstdout_fprintf (state_data->pstate,
		       stderr,
		       "%s:%s '%s' option not supported on this system\n",
		       state_data->prog_data->args->oem_id,
		       state_data->prog_data->args->oem_command,
		       state_data->prog_data->args->oem_options[0]);
      goto cleanup;
    }

  pstdout_printf (state_data->pstate,
		  "IP Address             : %s\n",
		  ip_address_buf);

  if (dhcp_or_static == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IP_ADDRESS_CONFIG_DHCP)
    dhcp_or_static_str = "DHCP";
  else if (dhcp_or_static == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IP_ADDRESS_CONFIG_STATIC)
    dhcp_or_static_str = "Static";
  else
    dhcp_or_static_str = "Unknown";

  pstdout_printf (state_data->pstate,
		  "IP Configuration       : %s\n",
		  dhcp_or_static_str);

  pstdout_printf (state_data->pstate,
		  "iDRAC Firmware Version : %s\n",
		  idrac_firmware_version_buf);

  if (idrac_type == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IDRAC_TYPE_10G)
    idrac_type_str = "Dell Poweredge 10G";
  else if (idrac_type == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IDRAC_TYPE_CMC)
    idrac_type_str = "Dell Chassis Management Controller ";
  else if (idrac_type == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IDRAC_TYPE_11G_MONOLITHIC)
    idrac_type_str = "Dell Poweredge 11G (Monolithic)";
  else if (idrac_type == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IDRAC_TYPE_11G_MODULAR)
    idrac_type_str = "Dell Poweredge 11G (Modular)";
  else if (idrac_type == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IDRAC_TYPE_MASER_LITE_BMC)
    idrac_type_str = "Maser Lite BMC";
  else if (idrac_type == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IDRAC_TYPE_12G_MONOLITHIC)
    idrac_type_str = "Dell Poweredge 12G (Monolithic)";
  else if (idrac_type == IPMI_OEM_DELL_SYSTEM_INFO_IDRAC_INFO_IDRAC_TYPE_12G_MODULAR)
    idrac_type_str = "Dell Poweredge 12G (Modular)";
  else
    idrac_type_str = "Unknown";

  pstdout_printf (state_data->pstate,
		  "iDRAC Type             : %s\n",
		  idrac_type_str);

  rv = 0;
 cleanup:
  return (rv);
}
