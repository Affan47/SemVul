fill_cmd_set_pef_configuration_parameters_pef_control (uint8_t pef,
                                                       uint8_t pef_event_messages,
                                                       uint8_t pef_startup_delay,
                                                       uint8_t pef_alert_startup_delay,
                                                       fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_PEF_VALID (pef)
      || !IPMI_PEF_EVENT_MESSAGES_VALID (pef_event_messages)
      || !IPMI_PEF_STARTUP_DELAY_VALID (pef_startup_delay)
      || !IPMI_PEF_ALERT_STARTUP_DELAY_VALID (pef_alert_startup_delay)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_pef_configuration_parameters_pef_control_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_PEF_CONFIGURATION_PARAMETERS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_selector", IPMI_PEF_CONFIGURATION_PARAMETER_PEF_CONTROL);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "pef", pef);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "pef_event_messages", pef_event_messages);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "pef_startup_delay", pef_startup_delay);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "pef_alert_startup_delay", pef_alert_startup_delay);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved2", 0);
  return (0);
}
