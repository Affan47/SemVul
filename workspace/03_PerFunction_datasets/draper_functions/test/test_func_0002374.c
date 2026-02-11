close()
{
  if (state() == Idle)
    return;

  if (state() == HostLookup)
    {
      d->peerResolver.cancel(false);
      d->localResolver.cancel(false);
    }

  d->localResults = d->peerResults = KResolverResults();

  socketDevice()->close();
  KActiveSocketBase::close();
  setState(Idle);
  emit stateChanged(Idle);
  emit closed();
}
