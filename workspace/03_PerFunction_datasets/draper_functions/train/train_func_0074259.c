bytesAvailable() const
{
  if (m_sockfd == -1)
    return -1;

  int nchars;
  if (kde_ioctl(m_sockfd, FIONREAD, &nchars) == -1)
    return -1;

  return nchars;
}
