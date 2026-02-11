ipmi_oem_inventec_get_nic_mode (ipmi_oem_state_data_t *state_data)
{
  uint32_t tmpvalue;
  int rv = -1;

  assert (state_data);
  assert (!state_data->prog_data->args->oem_options_count);


  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_NIC,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_NIC_MODE,
                                                    0,
                                                    1,
                                                    &tmpvalue) < 0)
    goto cleanup;

  switch (tmpvalue)
    {
    case IPMI_OEM_INVENTEC_EXTENDED_CONFIG_NIC_MODE_SHARED:
      pstdout_printf (state_data->pstate, "shared\n");
      break;
    case IPMI_OEM_INVENTEC_EXTENDED_CONFIG_NIC_MODE_DEDICATED:
      pstdout_printf (state_data->pstate, "dedicated\n");
      break;
    default:
      pstdout_printf (state_data->pstate, "unknown NIC mode: %Xh\n", tmpvalue);
      break;
    }

  rv = 0;
 cleanup:
  return (rv);
}
