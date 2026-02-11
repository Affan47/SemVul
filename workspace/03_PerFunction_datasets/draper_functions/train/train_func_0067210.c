sendrequest_inverse (address_t *ip)
{
  struct ipcache_item *rp = NULL;

  if (!ip)
      return;


  rp = ipcache_prepare_request(ip);


  struct ipresolve_link *newitm= (struct ipresolve_link *)malloc( sizeof(struct ipresolve_link));
  newitm->itemToResolve = rp;
  newitm->next= NULL;


  if (NULL == resolveListHead)
  {

     resolveListTail = resolveListHead = newitm;
  }
  else
  {
     resolveListTail->next = newitm;
     resolveListTail = newitm;
  }


  pthread_cond_signal(&resolvecond);

  g_my_debug("Resolver: queued request \"%s\".", strlongip (&rp->ip));
}
