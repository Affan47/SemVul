entry_guards_free_all(void)
{
  if (entry_guards) {
    SMARTLIST_FOREACH(entry_guards, entry_guard_t *, e,
                      entry_guard_free(e));
    smartlist_free(entry_guards);
    entry_guards = NULL;
  }
  clear_bridge_list();
  clear_transport_list();
  smartlist_free(bridge_list);
  smartlist_free(transport_list);
  bridge_list = NULL;
  transport_list = NULL;
}
