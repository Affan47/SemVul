_ipmi_lan_pkt_rq_min_size (uint8_t authentication_type, fiid_obj_t obj_cmd)
{
  unsigned int msg_len = 0;
  int len;

  assert (IPMI_1_5_AUTHENTICATION_TYPE_VALID (authentication_type) && fiid_obj_valid (obj_cmd));

  if ((len = fiid_template_len_bytes (tmpl_rmcp_hdr)) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  msg_len += len;

  if ((len = fiid_template_len_bytes (tmpl_lan_msg_hdr_rq)) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  msg_len += len;

  if ((len = fiid_template_len_bytes (tmpl_lan_msg_trlr)) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  msg_len += len;

  if ((len = fiid_template_block_len_bytes (tmpl_lan_session_hdr,
                                            "authentication_type",
                                            "session_id")) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  msg_len += len;

  if (authentication_type == IPMI_AUTHENTICATION_TYPE_MD2
      || authentication_type == IPMI_AUTHENTICATION_TYPE_MD5
      || authentication_type == IPMI_AUTHENTICATION_TYPE_STRAIGHT_PASSWORD_KEY
      || authentication_type == IPMI_AUTHENTICATION_TYPE_OEM_PROP)
    msg_len += IPMI_1_5_MAX_PASSWORD_LENGTH;

  if ((len = fiid_template_field_len_bytes (tmpl_lan_session_hdr, "ipmi_msg_len")) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  msg_len += len;

  if ((len = fiid_obj_len_bytes (obj_cmd)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }

  msg_len += len;

  return (msg_len);
}
