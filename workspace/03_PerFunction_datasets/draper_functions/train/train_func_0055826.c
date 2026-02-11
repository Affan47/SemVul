ipmi_oem_fujitsu_get_power_on_source (ipmi_oem_state_data_t *state_data)
{
  uint8_t source = 0;
  char str[IPMI_OEM_STR_BUFLEN];
  int rv = -1;

  assert (state_data);
  assert (!state_data->prog_data->args->oem_options_count);

  if (_ipmi_oem_get_power_source (state_data,
                                  IPMI_OEM_FUJITSU_COMMAND_SPECIFIER_GET_POWER_ON_SOURCE,
                                  &source) < 0)
    goto cleanup;

  memset (str, '\0', IPMI_OEM_STR_BUFLEN);

  if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_SOFTWARE_OR_COMMAND)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Software or command");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_POWER_SWITCH)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Power switch");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_AUTOMATIC_RESTART_AFTER_POWER_FAILURE)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Automatic restart after power failure");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_CLOCK_OR_TIMER)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Clock or timer");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_AUTOMATIC_RESTART_AFTER_FAN_FAILURE_SHUTDOWN)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Automatic restart after fan failure shutdown");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_AUTOMATIC_RESTART_AFTER_CRITICAL_TEMPERATURE_SHUTDOWN)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Automatic restart after critical temperature shutdown");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_REBOOT_AFTER_WATCHDOG_TIMEOUT)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Reboot after watchdog timeout");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_REMOTE_ON)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Remote on");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_REBOOT_AFTER_A_CPU_ERROR)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Reboot after a CPU error");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_REBOOT_BY_HARDWARE_RESET)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Reboot by hardware reset");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_REBOOT_AFTER_WARM_START)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Reboot after warm start");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_POWERED_ON_BY_A_PCI_BUS_POWER_MANAGEMENT_EVENT)
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Powered on by a PCI Bus Power Management Event");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_POWERED_ON_BY_REMOTE_CONTROL_VIA_REMOTE_MANAGER)

    snprintf (str, IPMI_OEM_STR_BUFLEN, "Powered on by remote control via Remote Manager");
  else if (source == IPMI_OEM_FUJITSU_POWER_ON_SOURCE_REBOOT_RESET_BY_REMOTE_CONTROL_VIA_REMOTE_MANAGER)

    snprintf (str, IPMI_OEM_STR_BUFLEN, "Reboot/reset by remote control via Remote Manager");
  else
    snprintf (str, IPMI_OEM_STR_BUFLEN, "Unrecognized source: %02Xh", source);

  pstdout_printf (state_data->pstate,
                  "%s\n",
                  str);

  rv = 0;
 cleanup:
  return (rv);
}
