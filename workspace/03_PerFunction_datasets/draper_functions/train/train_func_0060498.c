cres_mem(struct Client* sptr)
{
  struct dlink *dlink;
  struct reslist *request;
  size_t request_mem   = 0;
  int    request_count = 0;

  if (request_list.next) {
    for (dlink = request_list.next; dlink != &request_list; dlink = dlink->next) {
      request = (struct reslist*)dlink;
      request_mem += sizeof(*request);
      if (request->name)
        request_mem += strlen(request->name) + 1;
      ++request_count;
    }
  }

  send_reply(sptr, SND_EXPLICIT | RPL_STATSDEBUG,
	     ":Resolver: requests %d(%d)", request_count, request_mem);
  return request_mem;
}
