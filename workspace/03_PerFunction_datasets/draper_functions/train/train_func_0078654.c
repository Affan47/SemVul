bind(const KResolverEntry& address)
{
  if (socketDevice()->bind(address))
    {
      setError(NoError);

      d->state = KServerSocketPrivate::Bound;
      emit bound(address);
      return true;
    }
  copyError();
  return false;
}
