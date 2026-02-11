fill_cmd_set_pef_configuration_parameters_alert_strings (uint8_t string_selector,
                                                         uint8_t block_selector,
                                                         const uint8_t *string_data,
                                                         unsigned int string_data_len,
                                                         fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_STRING_SELECTOR_VALID (string_selector)
      || !string_data
      || !string_data_len
      || !IPMI_PEF_ALERT_STRINGS_BLOCK_SIZE_VALID (string_data_len)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_pef_configuration_parameters_alert_strings_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_PEF_CONFIGURATION_PARAMETERS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_selector", IPMI_PEF_CONFIGURATION_PARAMETER_ALERT_STRINGS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "string_selector", string_selector);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved2", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "block_selector", block_selector);
  FILL_FIID_OBJ_SET_DATA (obj_cmd_rq,
                          "string_data",
                          string_data,
                          string_data_len);

  return (0);
}
