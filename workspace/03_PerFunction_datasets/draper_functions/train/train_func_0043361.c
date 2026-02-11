AllowServerConnect(struct connectdata *conn)
{
  int timeout_ms;
  struct SessionHandle *data = conn->data;
  curl_socket_t sock = conn->sock[SECONDARYSOCKET];
  struct timeval now = Curl_tvnow();
  long timespent = Curl_tvdiff(Curl_tvnow(), now)/1000;
  long timeout = data->set.connecttimeout?data->set.connecttimeout:
    (data->set.timeout?data->set.timeout: 0);

  if(timeout) {
    timeout -= timespent;
    if(timeout<=0) {
      failf(data, "Timed out before server could connect to us");
      return CURLE_OPERATION_TIMEDOUT;
    }
  }


  timeout_ms = (timeout?(int)timeout:60) * 1000;

  switch (Curl_select(sock, CURL_SOCKET_BAD, timeout_ms)) {
  case -1:

    failf(data, "Error while waiting for server connect");
    return CURLE_FTP_PORT_FAILED;
  case 0:

    failf(data, "Timeout while waiting for server connect");
    return CURLE_FTP_PORT_FAILED;
  default:

    {
      curl_socket_t s = CURL_SOCKET_BAD;
#ifdef ENABLE_IPV6
      struct Curl_sockaddr_storage add;
#else
      struct sockaddr_in add;
#endif
      socklen_t size = (socklen_t) sizeof(add);

      if(0 == getsockname(sock, (struct sockaddr *) &add, &size)) {
        size = sizeof(add);

        s=accept(sock, (struct sockaddr *) &add, &size);
      }
      sclose(sock);

      if (CURL_SOCKET_BAD == s) {

        failf(data, "Error accept()ing server connect");
        return CURLE_FTP_PORT_FAILED;
      }
      infof(data, "Connection accepted from server\n");

      conn->sock[SECONDARYSOCKET] = s;
      Curl_nonblock(s, TRUE);
    }
    break;
  }

  return CURLE_OK;
}
