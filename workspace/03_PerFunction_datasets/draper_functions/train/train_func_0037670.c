toplevel_destroy(Toplevel *toplevel)
{
  if (toplevel != NULL) {
    toplevel_delete(toplevel);
    toplevels = g_slist_remove(toplevels, toplevel);
  }
}
