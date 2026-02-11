close()
{
  d->reply = d->request = QByteArray();
  d->peer = KSocketAddress();
  KSocketDevice::close();
}
