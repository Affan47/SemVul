_gnutls_ia_server_handshake (gnutls_session_t session)
{
  gnutls_ia_apptype_t msg_type;
  ssize_t len;
  char buf[1024];
  int ret;
  const struct gnutls_ia_server_credentials_st *cred =
    _gnutls_get_cred (session->key, GNUTLS_CRD_IA, NULL);

  if (cred == NULL)
    return GNUTLS_E_INTERNAL_ERROR;

  do
    {
      char *avp;
      size_t avplen;

      len = gnutls_ia_recv (session, buf, sizeof (buf));
      if (len == GNUTLS_E_WARNING_IA_IPHF_RECEIVED ||
          len == GNUTLS_E_WARNING_IA_FPHF_RECEIVED)
        {
          ret = gnutls_ia_verify_endphase (session, buf);
          if (ret < 0)
            return ret;
        }

      if (len == GNUTLS_E_WARNING_IA_IPHF_RECEIVED)
        continue;
      else if (len == GNUTLS_E_WARNING_IA_FPHF_RECEIVED)
        break;

      if (len < 0)
        return len;

      avp = NULL;
      avplen = 0;

      ret = cred->avp_func (session, cred->avp_ptr, buf, len, &avp, &avplen);
      if (ret < 0)
        {
          int tmpret;
          tmpret = gnutls_alert_send (session, GNUTLS_AL_FATAL,
                                      GNUTLS_A_INNER_APPLICATION_FAILURE);
          if (tmpret < 0)
            gnutls_assert ();
          return ret;
        }

      msg_type = ret;

      if (msg_type != GNUTLS_IA_APPLICATION_PAYLOAD)
        {
          ret = gnutls_ia_endphase_send (session, msg_type ==
                                         GNUTLS_IA_FINAL_PHASE_FINISHED);
          if (ret < 0)
            return ret;
        }
      else
        {
          len = gnutls_ia_send (session, avp, avplen);
          gnutls_free (avp);
          if (len < 0)
            return len;
        }
    }
  while (1);

  return 0;
}
