_deconstruct_payload_rakp (uint8_t payload_type,
                           fiid_obj_t obj_rmcpplus_payload,
                           fiid_obj_t obj_cmd,
                           const void *pkt,
                           uint16_t ipmi_payload_len)
{
  assert ((payload_type == IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_RESPONSE
           || payload_type == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_2
           || payload_type == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_4)
          && fiid_obj_valid (obj_cmd)
          && !(payload_type == IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_RESPONSE
               && fiid_obj_template_compare (obj_cmd, tmpl_rmcpplus_open_session_response) < 0)
          && !(payload_type == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_2
               && fiid_obj_template_compare (obj_cmd, tmpl_rmcpplus_rakp_message_2) < 0)
          && !(payload_type == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_4
               && fiid_obj_template_compare (obj_cmd, tmpl_rmcpplus_rakp_message_4) < 0)
          && fiid_obj_valid (obj_rmcpplus_payload)
          && fiid_obj_template_compare (obj_rmcpplus_payload, tmpl_rmcpplus_payload) == 1
          && pkt
          && ipmi_payload_len);

  if (fiid_obj_set_data (obj_rmcpplus_payload,
                         "payload_data",
                         pkt,
                         ipmi_payload_len) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_rmcpplus_payload);
      return (-1);
    }

  if (fiid_obj_set_all (obj_cmd,
                        pkt,
                        ipmi_payload_len) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }

  return (1);
}
