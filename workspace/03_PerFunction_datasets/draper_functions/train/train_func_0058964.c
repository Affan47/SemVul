_ecore_con_ssl_client_write_gnutls(Ecore_Con_Client *cl,
                                   const unsigned char *buf,
                                   int               size)
{
   int num;

   if (cl->ssl_state == ECORE_CON_SSL_STATE_HANDSHAKING)
     {
        if (!_ecore_con_ssl_client_init_gnutls(cl))
          return 0;
        return -1;
     }

   num = gnutls_record_send(cl->session, buf, size);
   if (num > 0)
     return num;

   if (num == GNUTLS_E_REHANDSHAKE)
     {
        WRN("Rehandshake request ignored");
        return 0;
        cl->handshaking = EINA_TRUE;
        cl->ssl_state = ECORE_CON_SSL_STATE_HANDSHAKING;
        if (!_ecore_con_ssl_client_init_gnutls(cl))
          return 0;
     }
   else if (!gnutls_error_is_fatal(num))
     return 0;

   return -1;
}
