_check_for_ipmi_2_0_support (ipmiconsole_ctx_t c)
{
  int ret;

  assert (c);
  assert (c->magic == IPMICONSOLE_CTX_MAGIC);
  assert (c->session.protocol_state == IPMICONSOLE_PROTOCOL_STATE_GET_AUTHENTICATION_CAPABILITIES_SENT);

  if ((ret = ipmi_check_authentication_capabilities_ipmi_2_0 (c->connection.obj_authentication_capabilities_rs)) < 0)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("ipmi_check_authentication_capabilities_ipmi_2_0: %s", strerror (errno)));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
      return (-1);
    }

  if (!ret)
    {
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_IPMI_2_0_UNAVAILABLE);
      return (-1);
    }

  return (0);
}
