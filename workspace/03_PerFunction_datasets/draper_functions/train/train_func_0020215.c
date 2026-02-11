ftpSize(const QString & path, char mode)
{
  m_size = UnknownSize;
  if (!ftpDataMode(mode)) {
    return false;
  }

  const QByteArray psz(ftpSendSizeCmd(path));
  if (psz.isEmpty()) {
    return false;
  }

  bool ok = false;
  m_size = psz.trimmed().toLongLong(&ok);
  if (!ok) {
    m_size = UnknownSize;
  }

  return true;
}
