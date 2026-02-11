ha_lock_engine(THD *thd, const handlerton *hton)
{
  if (hton)
  {
    st_plugin_int **plugin= hton2plugin + hton->slot;

#ifdef DBUG_OFF
    return my_plugin_lock(thd, plugin);
#else
    return my_plugin_lock(thd, &plugin);
#endif
  }
  return NULL;
}
