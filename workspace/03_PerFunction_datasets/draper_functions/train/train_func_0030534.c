HTTPFindPassword(hi, realm, hostname, port)
HTTPInfo *hi;
char *realm;
char *hostname;
int port;
{
  HTTPPassword *hp;

  port = port == 0 ? 80:port;

  for (hp = (HTTPPassword *)GListGetHead(hi->hc->passwords); hp != NULL;
       hp = (HTTPPassword *)GListGetNext(hi->hc->passwords))
  {
    if (strlen(realm) == strlen(hp->realm) &&
	strcmp(realm, hp->realm) == 0 &&
	strlen(hostname) == strlen(hp->hostname) &&
	strcasecmp(hostname, hp->hostname) == 0 &&
	port == hp->port)
    {
      return(hp);
    }
  }

  return(NULL);
}
