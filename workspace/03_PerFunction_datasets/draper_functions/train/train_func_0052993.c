peerport() const
{
  sockinetaddr sin = peeraddr();
  if (sin.family() != af_inet) return -1;
  return sin.getport();
}
