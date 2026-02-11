find_id(int id)
{
  struct dlink *ptr;
  struct reslist *request;

  for (ptr = request_list.next; ptr != &request_list; ptr = ptr->next)
  {
    request = (struct reslist*)ptr;

    if (request->id == id) {
      Debug((DEBUG_DNS, "find_id(%d) -> %p", id, request));
      return(request);
    }
  }

  Debug((DEBUG_DNS, "find_id(%d) -> NULL", id));
  return(NULL);
}
