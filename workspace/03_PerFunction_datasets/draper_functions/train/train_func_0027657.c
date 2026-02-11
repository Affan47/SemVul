lookup (int type, char *key, struct servent *resultbufp, char *buffer,
	size_t buflen, struct servent **serv)
{
  char *proto = strrchr (key, '/');
  if (proto != NULL && proto != key)
    {
      key = strndupa (key, proto - key);
      if (proto[1] == '\0')
	proto = NULL;
      else
	++proto;
    }

  if (type == GETSERVBYNAME)
    return __getservbyname_r (key, proto, resultbufp, buffer, buflen, serv);

  assert (type == GETSERVBYPORT);
  return __getservbyport_r (atol (key), proto, resultbufp, buffer, buflen,
			    serv);
}
