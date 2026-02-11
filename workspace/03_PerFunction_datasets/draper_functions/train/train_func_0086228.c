Curl_ipv6works(void)
{


  static int ipv6_works = -1;
  if(-1 == ipv6_works) {

    curl_socket_t s = socket(PF_INET6, SOCK_DGRAM, 0);
    if(s == CURL_SOCKET_BAD)

      ipv6_works = 0;
    else {
      ipv6_works = 1;
      Curl_closesocket(NULL, s);
    }
  }
  return (ipv6_works>0)?TRUE:FALSE;
}
