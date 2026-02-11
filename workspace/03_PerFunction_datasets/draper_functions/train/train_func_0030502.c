fill_cmd_set_front_panel_enables (uint8_t disable_power_off_button_for_power_off_only,
                                  uint8_t disable_reset_button,
                                  uint8_t disable_diagnostic_interrupt_button,
                                  uint8_t disable_standby_button_for_entering_standby,
                                  fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_CHASSIS_BUTTON_VALID (disable_power_off_button_for_power_off_only)
      || !IPMI_CHASSIS_BUTTON_VALID (disable_reset_button)
      || !IPMI_CHASSIS_BUTTON_VALID (disable_diagnostic_interrupt_button)
      || !IPMI_CHASSIS_BUTTON_VALID (disable_standby_button_for_entering_standby)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_front_panel_enables_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);

  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_FRONT_PANEL_ENABLES);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "disable_power_off_button_for_power_off_only", disable_power_off_button_for_power_off_only);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "disable_reset_button", disable_reset_button);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "disable_diagnostic_interrupt_button", disable_diagnostic_interrupt_button);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "disable_standby_button_for_entering_standby", disable_standby_button_for_entering_standby);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved", 0);

  return (0);
}
