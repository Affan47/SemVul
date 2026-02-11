setError(SocketError error)
{
  KSocketBase::setError(error);
  setErrorString(KSocketBase::errorString());
}
