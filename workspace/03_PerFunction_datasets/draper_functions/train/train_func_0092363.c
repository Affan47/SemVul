_fill_lan_mac_address (uint8_t parameter_selector,
                       uint8_t channel_number,
                       uint64_t mac_address,
                       fiid_obj_t obj_cmd_rq)
{
  assert ((parameter_selector == IPMI_LAN_CONFIGURATION_PARAMETER_MAC_ADDRESS
           || parameter_selector == IPMI_LAN_CONFIGURATION_PARAMETER_DEFAULT_GATEWAY_MAC_ADDRESS
           || parameter_selector == IPMI_LAN_CONFIGURATION_PARAMETER_BACKUP_GATEWAY_MAC_ADDRESS)
          && IPMI_CHANNEL_NUMBER_VALID (channel_number)
          && fiid_obj_valid (obj_cmd_rq));

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_LAN_CONFIGURATION_PARAMETERS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "channel_number", channel_number);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_selector", parameter_selector);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "mac_address", mac_address);

  return (0);
}
