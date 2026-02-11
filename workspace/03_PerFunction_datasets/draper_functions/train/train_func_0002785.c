ipmi_oem_fujitsu_get_power_off_source (ipmi_oem_state_data_t *state_data)
{
  uint8_t source = 0;
  char str[IPMI_OEM_STR_BUFLEN];
  int rv = -1;

  assert (state_data);
  assert (!state_data->prog_data->args->oem_options_count);

  if (_ipmi_oem_get_power_source (state_data,
                                  IPMI_OEM_FUJITSU_COMMAND_SPECIFIER_GET_POWER_OFF_SOURCE,
                                  &source) < 0)
    goto cleanup;

  memset (str, '\0', IPMI_OEM_STR_BUFLEN);

  if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_SOFTWARE)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Software or command");
  else if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_POWER_SWITCH)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Power switch");
  else if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_AC_POWER_FAIL)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "AC power fail");
  else if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_CLOCK_OR_TIMER)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Clock or timer");
  else if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_FAN_FAILURE)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Fan failure");
  else if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_CRITICAL_TEMPERATURE)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Critical temperature");
  else if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_FINAL_POWER_OFF_AFTER_REPEATED_WATCHDOG_TIMEOUTS)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Final power-off after repeated watchdog timeouts");
  else if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_FINAL_POWER_OFF_AFTER_REPEATED_CPU_ERRORS)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Final power-off after repeated CPU errors");
  else if (source == IPMI_OEM_FUJITSU_POWER_OFF_SOURCE_POWERED_OFF_BY_REMOTE_CONTROL_VIA_REMOTE_MANAGER)

    snprintf (str, IPMI_OEM_STR_BUFLEN, "Powered off by remote control via Remote Manager");
  else
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Unrecognized source: %02Xh", source);

  pstdout_printf (state_data->pstate,
                  "%s\n",
                  str);

  rv = 0;
 cleanup:
  return (rv);
}
