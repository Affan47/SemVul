ipmi_oem_inventec_get_power_management_config (ipmi_oem_state_data_t *state_data)
{
  uint32_t tmpvalue;
  uint8_t powermanagementenable;
  uint8_t dpnmpowermanagement;
  uint8_t powerstaggeringacrecovery;
  uint16_t powerondelay;
  uint16_t minpowerondelay;
  uint16_t maxpowerondelay;
  int rv = -1;

  assert (state_data);
  assert (!state_data->prog_data->args->oem_options_count);

  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_POWER_MANAGEMENT,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_POWER_MANAGEMENT_POWER_MANAGEMENT_ENABLE,
                                                    0,
                                                    1,
                                                    &tmpvalue) < 0)
    goto cleanup;
  powermanagementenable = tmpvalue;

  dpnmpowermanagement = (powermanagementenable & IPMI_OEM_INVENTEC_EXTENDED_CONFIG_POWER_MANAGEMENT_ENABLE_DPNM_BITMASK);
  dpnmpowermanagement >>= IPMI_OEM_INVENTEC_EXTENDED_CONFIG_POWER_MANAGEMENT_ENABLE_DPNM_SHIFT;

  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_POWER_MANAGEMENT,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_POWER_MANAGEMENT_POWER_STAGGERING_AC_RECOVERY,
                                                    0,
                                                    1,
                                                    &tmpvalue) < 0)
    goto cleanup;
  powerstaggeringacrecovery = tmpvalue;

  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_POWER_MANAGEMENT,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_POWER_MANAGEMENT_POWER_ON_DELAY,
                                                    0,
                                                    2,
                                                    &tmpvalue) < 0)
    goto cleanup;
  powerondelay = tmpvalue;

  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_POWER_MANAGEMENT,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_POWER_MANAGEMENT_MINIMUM_POWER_ON_DELAY,
                                                    0,
                                                    2,
                                                    &tmpvalue) < 0)
    goto cleanup;
  minpowerondelay = tmpvalue;

  if (_ipmi_oem_inventec_get_extended_config_value (state_data,
                                                    IPMI_OEM_INVENTEC_EXTENDED_CONFIGURATION_ID_POWER_MANAGEMENT,
                                                    IPMI_OEM_INVENTEC_EXTENDED_ATTRIBUTE_ID_POWER_MANAGEMENT_MAXIMUM_POWER_ON_DELAY,
                                                    0,
                                                    2,
                                                    &tmpvalue) < 0)
    goto cleanup;
  maxpowerondelay = tmpvalue;

  pstdout_printf (state_data->pstate,
		  "DPNM Power Management        : %s\n",
		  (dpnmpowermanagement) ? "Enabled" : "Disabled");

  if (powerstaggeringacrecovery == IPMI_OEM_INVENTEC_EXTENDED_CONFIG_POWER_STAGGERING_AC_RECOVERY_IMMEDIATE)
    pstdout_printf (state_data->pstate,
                    "Power Staggering AC Recovery : Immediate\n");
  else if (powerstaggeringacrecovery == IPMI_OEM_INVENTEC_EXTENDED_CONFIG_POWER_STAGGERING_AC_RECOVERY_AUTO)
    pstdout_printf (state_data->pstate,
                    "Power Staggering AC Recovery : Auto\n");
  else if (powerstaggeringacrecovery == IPMI_OEM_INVENTEC_EXTENDED_CONFIG_POWER_STAGGERING_AC_RECOVERY_USER_DEFINED)
    pstdout_printf (state_data->pstate,
                    "Power Staggering AC Recovery : User Defined\n");
  else
    pstdout_printf (state_data->pstate,
                    "Power Staggering AC Recovery : %Xh\n",
                    powerstaggeringacrecovery);

  pstdout_printf (state_data->pstate,
		  "Power On Delay               : %u seconds\n",
                  powerondelay);

  pstdout_printf (state_data->pstate,
		  "Minimum Power On Delay       : %u seconds\n",
                  minpowerondelay);

  pstdout_printf (state_data->pstate,
		  "Maximum Power On Delay       : %u seconds\n",
                  maxpowerondelay);

  rv = 0;
 cleanup:
  return (rv);
}
