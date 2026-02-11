whowas_free(struct Whowas *ww)
{
  if (!ww)
    return;

  Debug((DEBUG_LIST, "Destroying whowas structure for %s", ww->name));

  whowas_clean(ww);
  MyFree(ww);

  wwList.ww_alloc--;
}
