Scm_TLSWrite(ScmTLS* t, ScmObj msg)
{
#if defined(GAUCHE_USE_AXTLS)
  int r; u_int size; const uint8_t* cmsg;
  close_check(t, "write");
  cmsg = get_message_body(msg, &size);
  if ((r = ssl_write(t->conn, cmsg, size)) < 0)
    Scm_SysError("ssl_write() failed");
  return SCM_MAKE_INT(r);
#else
  return SCM_FALSE;
#endif
}
