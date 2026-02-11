ipmiconsole_packet_dump_unknown (ipmiconsole_ctx_t c,
                                 const void *buf,
                                 unsigned int buflen)
{
  char hdr[IPMICONSOLE_MAX_PACKET_DUMP_HDR_LEN];
  int fd;
  int ret;

  assert (c);
  assert (c->magic == IPMICONSOLE_CTX_MAGIC);
  assert (buf);
  assert (buflen);

  if (c->config.debug_flags & IPMICONSOLE_DEBUG_STDOUT)
    fd = STDOUT_FILENO;
  else if (c->config.debug_flags & IPMICONSOLE_DEBUG_STDERR)
    fd = STDERR_FILENO;
  else if (c->config.debug_flags & IPMICONSOLE_DEBUG_FILE)
    fd = c->debug.debug_fd;
  else
    return (0);

  if (_packet_dump_unknown_hdr (c, buf, buflen, hdr, IPMICONSOLE_MAX_PACKET_DUMP_HDR_LEN) < 0)
    return (-1);

  if ((ret = ipmi_is_ipmi_1_5_packet (buf, buflen)) < 0)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("ipmi_is_ipmi_1_5_packet: %s", strerror (errno)));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
      return (-1);
    }

  if (ret)
    {
      if (ipmi_dump_lan_packet (fd,
                                c->config.hostname,
                                hdr,
                                NULL,
                                buf,
                                buflen,
                                tmpl_lan_msg_hdr_rs,
                                tmpl_unexpected_data) < 0)
        {
          IPMICONSOLE_CTX_DEBUG (c, ("ipmi_dump_lan_packet: %s", strerror (errno)));
          ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
          return (-1);
        }
    }
  else
    {
      if (ipmi_dump_rmcpplus_packet (fd,
                                     c->config.hostname,
                                     hdr,
                                     NULL,
                                     c->config.authentication_algorithm,
                                     c->config.integrity_algorithm,
                                     c->config.confidentiality_algorithm,
                                     c->session.integrity_key_ptr,
                                     c->session.integrity_key_len,
                                     c->session.confidentiality_key_ptr,
                                     c->session.confidentiality_key_len,
                                     buf,
                                     buflen,
                                     tmpl_lan_msg_hdr_rs,
                                     tmpl_unexpected_data) < 0)
        {
          IPMICONSOLE_CTX_DEBUG (c, ("ipmi_dump_rmcpplus_packet: %s", strerror (errno)));
          ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
          return (-1);
        }
    }

  return (0);
}
