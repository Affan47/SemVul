ipmiconsole_check_rmcpplus_status_code (ipmiconsole_ctx_t c, ipmiconsole_packet_type_t p)
{
  uint8_t rmcpplus_status_code;
  uint64_t val;
  fiid_obj_t obj_cmd;

  assert (c);
  assert (c->magic == IPMICONSOLE_CTX_MAGIC);
  assert (IPMICONSOLE_PACKET_TYPE_RESPONSE (p));
  assert (p == IPMICONSOLE_PACKET_TYPE_OPEN_SESSION_RESPONSE
          || p == IPMICONSOLE_PACKET_TYPE_RAKP_MESSAGE_2
          || p == IPMICONSOLE_PACKET_TYPE_RAKP_MESSAGE_4);

  obj_cmd = ipmiconsole_packet_object (c, p);
  if (FIID_OBJ_GET (obj_cmd,
                    "rmcpplus_status_code",
                    &val) < 0)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("FIID_OBJ_GET: 'rmcpplus_status_code': %s",
                                 fiid_obj_errormsg (obj_cmd)));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
      return (-1);
    }
  rmcpplus_status_code = val;

  if (rmcpplus_status_code != RMCPPLUS_STATUS_NO_ERRORS)
    IPMICONSOLE_CTX_DEBUG (c, ("rmcpplus status code check failed; p = %d", p));

  return ((rmcpplus_status_code == RMCPPLUS_STATUS_NO_ERRORS) ? 1 : 0);
}
