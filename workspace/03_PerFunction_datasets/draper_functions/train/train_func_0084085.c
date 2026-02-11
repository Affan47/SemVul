_construct_session_trlr_pad (uint8_t integrity_algorithm,
                             unsigned int ipmi_msg_len,
                             fiid_obj_t obj_rmcpplus_session_trlr)
{
  int pad_length_field_len, next_header_field_len;
  unsigned int pad_length = 0;
  uint8_t pad_bytes[IPMI_INTEGRITY_PAD_MULTIPLE] = { IPMI_INTEGRITY_PAD_DATA,
                                                     IPMI_INTEGRITY_PAD_DATA,
                                                     IPMI_INTEGRITY_PAD_DATA,
                                                     IPMI_INTEGRITY_PAD_DATA};

  assert (IPMI_INTEGRITY_ALGORITHM_SUPPORTED (integrity_algorithm)
          && fiid_obj_valid (obj_rmcpplus_session_trlr)
          && fiid_obj_template_compare (obj_rmcpplus_session_trlr, tmpl_rmcpplus_session_trlr) == 1);

  if ((pad_length_field_len = fiid_template_field_len_bytes (tmpl_rmcpplus_session_trlr,
                                                             "pad_length")) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  if ((next_header_field_len = fiid_template_field_len_bytes (tmpl_rmcpplus_session_trlr,
                                                              "next_header")) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  ipmi_msg_len += pad_length_field_len;
  ipmi_msg_len += next_header_field_len;

  if (ipmi_msg_len % IPMI_INTEGRITY_PAD_MULTIPLE)
    pad_length = IPMI_INTEGRITY_PAD_MULTIPLE - (ipmi_msg_len % IPMI_INTEGRITY_PAD_MULTIPLE);

  if (pad_length)
    {
      if (fiid_obj_set_data (obj_rmcpplus_session_trlr,
                             "integrity_pad",
                             pad_bytes,
                             pad_length) < 0)
        {
          FIID_OBJECT_ERROR_TO_ERRNO (obj_rmcpplus_session_trlr);
          return (-1);
        }
    }

  if (fiid_obj_set (obj_rmcpplus_session_trlr,
                    "pad_length",
                    pad_length) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_rmcpplus_session_trlr);
      return (-1);
    }

  return (0);
}
