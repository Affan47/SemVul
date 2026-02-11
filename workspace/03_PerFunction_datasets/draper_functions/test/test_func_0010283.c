close()
{
  resetError();
  if (m_sockfd != -1)
    {
      delete d->input;
      delete d->output;
      delete d->exception;

      d->input = d->output = d->exception = 0L;
#ifdef Q_WS_WIN
      ::closesocket(m_sockfd);
#else
      d->local.setFamily(AF_UNSPEC);
      d->peer.setFamily(AF_UNSPEC);

      ::close(m_sockfd);
#endif
    }
  setOpenMode(0);

  m_sockfd = -1;
}
