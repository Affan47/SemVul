fill_cmd_set_lan_configuration_parameters_destination_addresses (uint8_t channel_number,
                                                                 uint8_t destination_selector,
                                                                 uint8_t gateway_selector,
                                                                 uint32_t alerting_ip_address,
                                                                 uint64_t alerting_mac_address,
                                                                 fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_CHANNEL_NUMBER_VALID (channel_number)
      || !IPMI_DESTINATION_SELECTOR_VALID (destination_selector)
      || !IPMI_GATEWAY_SELECTOR_VALID (gateway_selector)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_lan_configuration_parameters_destination_addresses_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_LAN_CONFIGURATION_PARAMETERS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "channel_number", channel_number);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_selector", IPMI_LAN_CONFIGURATION_PARAMETER_DESTINATION_ADDRESSES);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "destination_selector", destination_selector);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved2", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved3", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "address_format", IPMI_ADDRESS_FORMAT_IPV4);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "gateway_selector", gateway_selector);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved4", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "alerting_ip_address", alerting_ip_address);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "alerting_mac_address", alerting_mac_address);

  return (0);
}
