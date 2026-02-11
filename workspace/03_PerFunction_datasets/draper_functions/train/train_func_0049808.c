Curl_gtls_shutdown(struct connectdata *conn, int sockindex)
{
  ssize_t result;
  int retval = 0;
  struct SessionHandle *data = conn->data;
  int done = 0;
  char buf[120];


  if(data->set.ftp_ccc == CURLFTPSSL_CCC_ACTIVE)
      gnutls_bye(conn->ssl[sockindex].session, GNUTLS_SHUT_WR);

  if(conn->ssl[sockindex].session) {
    while(!done) {
      int what = Curl_socket_ready(conn->sock[sockindex],
                                   CURL_SOCKET_BAD, SSL_SHUTDOWN_TIMEOUT);
      if(what > 0) {


        result = gnutls_record_recv(conn->ssl[sockindex].session,
                                    buf, sizeof(buf));
        switch(result) {
        case 0:


          done = 1;
          break;
        case GNUTLS_E_AGAIN:
        case GNUTLS_E_INTERRUPTED:
          infof(data, "GNUTLS_E_AGAIN || GNUTLS_E_INTERRUPTED\n");
          break;
        default:
          retval = -1;
          done = 1;
          break;
        }
      }
      else if(0 == what) {

        failf(data, "SSL shutdown timeout");
        done = 1;
        break;
      }
      else {

        failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
        retval = -1;
        done = 1;
      }
    }
    gnutls_deinit(conn->ssl[sockindex].session);
  }
  gnutls_certificate_free_credentials(conn->ssl[sockindex].cred);

#ifdef USE_TLS_SRP
  if(data->set.ssl.authtype == CURL_TLSAUTH_SRP
     && data->set.ssl.username != NULL)
    gnutls_srp_free_client_credentials(conn->ssl[sockindex].srp_client_cred);
#endif

  conn->ssl[sockindex].cred = NULL;
  conn->ssl[sockindex].session = NULL;

  return retval;
}
