exact_comp (table_t * ptr, CTL_MSG * request, time_t * now)
{
  if (request->type == ptr->request.type
      && request->pid == ptr->request.pid
      && strcmp (request->r_name, ptr->request.r_name) == 0
      && strcmp (request->l_name, ptr->request.l_name) == 0)
    {
      ptr->time = *now;
      return 0;
    }
  return 1;
}
