http_write(char https, SslFd* sf, unsigned char* buf, int amount)
{
  if (https) {
    return SSL_writen(SslFd_get_ssl(sf), buf, amount);
  }
  else {
    return writen(SslFd_get_fd(sf), buf, amount);
  }
}
