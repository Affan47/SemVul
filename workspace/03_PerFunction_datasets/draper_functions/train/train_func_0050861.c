_construct_payload_rakp (uint8_t payload_type,
                         fiid_obj_t obj_cmd,
                         fiid_obj_t obj_rmcpplus_payload)
{
  uint8_t obj_cmd_buf[IPMI_MAX_PAYLOAD_LENGTH];
  int obj_cmd_len = 0;

  assert ((payload_type == IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_REQUEST
           || payload_type == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_1
           || payload_type == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_3)
          && fiid_obj_valid (obj_cmd)
          && !(payload_type == IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_REQUEST
               && fiid_obj_template_compare (obj_cmd, tmpl_rmcpplus_open_session_request) < 0)
          && !(payload_type == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_1
               && fiid_obj_template_compare (obj_cmd, tmpl_rmcpplus_rakp_message_1) < 0)
          && !(payload_type == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_3
               && fiid_obj_template_compare (obj_cmd, tmpl_rmcpplus_rakp_message_3) < 0)
          && fiid_obj_valid (obj_rmcpplus_payload)
          && fiid_obj_template_compare (obj_rmcpplus_payload, tmpl_rmcpplus_payload) == 1
          && fiid_obj_packet_valid (obj_cmd) == 1);

  if ((obj_cmd_len = fiid_obj_get_all (obj_cmd,
                                       obj_cmd_buf,
                                       IPMI_MAX_PAYLOAD_LENGTH)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }

  if (fiid_obj_set_data (obj_rmcpplus_payload,
                         "payload_data",
                         obj_cmd_buf,
                         obj_cmd_len) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_rmcpplus_payload);
      return (-1);
    }

  return (obj_cmd_len);
}
