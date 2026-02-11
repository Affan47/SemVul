fill_cmd_set_lan_configuration_parameters_vlan_priority (uint8_t channel_number,
                                                         uint8_t vlan_priority,
                                                         fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_CHANNEL_NUMBER_VALID (channel_number)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_lan_configuration_parameters_vlan_priority_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_LAN_CONFIGURATION_PARAMETERS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "channel_number", channel_number);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_selector", IPMI_LAN_CONFIGURATION_PARAMETER_VLAN_PRIORITY);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "vlan_priority", vlan_priority);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "unspecified", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved2", 0);

  return (0);
}
