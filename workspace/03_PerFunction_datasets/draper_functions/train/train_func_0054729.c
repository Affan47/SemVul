fill_cmd_set_acpi_power_state (uint8_t system_power_state_enumeration,
                               uint8_t set_system_power_state,
                               uint8_t device_power_state_enumeration,
                               uint8_t set_device_power_state,
                               fiid_obj_t obj_cmd_rq)
{

  if (!IPMI_ACPI_SET_SYSTEM_POWER_STATE_VALID (set_system_power_state)
      || (set_system_power_state == IPMI_ACPI_SET_SYSTEM_POWER_STATE_SET_SYSTEM_POWER_STATE
          && !IPMI_ACPI_SYSTEM_POWER_STATE_VALID (system_power_state_enumeration))
      || !IPMI_ACPI_SET_DEVICE_POWER_STATE_VALID (set_device_power_state)
      || (set_device_power_state == IPMI_ACPI_SET_DEVICE_POWER_STATE_SET_DEVICE_POWER_STATE
          && !IPMI_ACPI_DEVICE_POWER_STATE_VALID (device_power_state_enumeration))
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_acpi_power_state_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_ACPI_POWER_STATE);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "system_power_state_enumeration", system_power_state_enumeration);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "set_system_power_state", set_system_power_state);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "device_power_state_enumeration", device_power_state_enumeration);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "set_device_power_state", set_device_power_state);
  return (0);
}
