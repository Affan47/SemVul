ipmi_oem_inventec_get_authentication_config (ipmi_oem_state_data_t *state_data)
{
  uint32_t tmpvalue;
  uint8_t maxauthenticationfailures;
  uint16_t lockoutwindow;
  uint16_t lockouttime;
  int rv = -1;

  assert (state_data);
  assert (!state_data->prog_data->args->oem_options_count);

  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_SECURITY,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_SECURITY_MAX_AUTHENTICATION_FAILURES,
                                                    0,
                                                    1,
                                                    &tmpvalue) < 0)
    goto cleanup;
  maxauthenticationfailures = tmpvalue;

  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_SECURITY,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_SECURITY_LOCKOUT_WINDOW,
                                                    0,
                                                    2,
                                                    &tmpvalue) < 0)
    goto cleanup;
  lockoutwindow = tmpvalue;

  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_SECURITY,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_SECURITY_LOCKOUT_TIME,
                                                    0,
                                                    2,
                                                    &tmpvalue) < 0)
    goto cleanup;
  lockouttime = tmpvalue;

  pstdout_printf (state_data->pstate,
		  "Max Authentication Failures : %u\n",
                  maxauthenticationfailures);

  pstdout_printf (state_data->pstate,
		  "Lockout Window              : %u seconds\n",
		  lockoutwindow);

  pstdout_printf (state_data->pstate,
		  "Lockout Time                : %u seconds\n",
		  lockouttime);

  rv = 0;
 cleanup:
  return (rv);
}
