__request(CONN *C, URL U, CLIENT *client) {
  C->scheme = url_get_scheme(U);

  switch (C->scheme) {
    case FTP:
      return __ftp(C, U, client);
    case HTTP:
    case HTTPS:
    default:
      return __http(C, U, client);
  }
}
