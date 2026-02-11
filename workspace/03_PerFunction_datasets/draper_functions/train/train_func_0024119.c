prepend_unset_notify (GSList       *notifies,
		      GConfSources *modified_sources,
		      char         *key)
{
  GConfUnsetNotify *notify;

  g_assert (modified_sources != NULL);
  g_assert (key != NULL);

  notify = g_new0 (GConfUnsetNotify, 1);

  notify->modified_sources = modified_sources;
  notify->key              = key;

  return g_slist_append (notifies, notify);
}
