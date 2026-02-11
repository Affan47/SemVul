doBind()
{
  d->bindWhenFound = false;


  KResolverResults::ConstIterator it = d->resolverResults.constBegin();
  for ( ; it != d->resolverResults.constEnd(); ++it)
    if (bind(*it))
      {
	if (d->listenWhenBound)
	  return doListen();
	return true;
      }
    else
      socketDevice()->close();


  emit gotError(error());
  return false;
}
