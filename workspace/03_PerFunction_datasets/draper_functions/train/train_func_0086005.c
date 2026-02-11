get_additional_sources (GrlSource *source,
                        GrlMedia *media,
                        GList *keys,
                        GList **additional_keys,
                        gboolean main_source_is_only_resolver)
{
  GList *missing_keys, *iter, *result = NULL, *sources;
  GrlRegistry *registry;

  missing_keys = missing_in_data (GRL_DATA (media), keys);
  if (!missing_keys)
    return NULL;

  registry = grl_registry_get_default ();
  sources = grl_registry_get_sources_by_operations (registry,
                                                    GRL_OP_RESOLVE,
                                                    TRUE);

  for (iter = missing_keys; iter; iter = g_list_next (iter)) {
    GrlKeyID key = GRLPOINTER_TO_KEYID (iter->data);
    GrlSource *_source;
    GList *needed_keys = NULL;

    _source = get_additional_source_for_key (source, sources, media, key,
                                             additional_keys?&needed_keys:NULL,
                                             main_source_is_only_resolver);
    if (_source) {
      result = g_list_append (result, _source);

      if (needed_keys)
        *additional_keys = list_union (*additional_keys, needed_keys, NULL);

      GRL_INFO ("%s can resolve %s %s",
                grl_source_get_name (_source),
                GRL_METADATA_KEY_GET_NAME (key),
                needed_keys? "with more keys" : "directly");

    } else {
      GRL_DEBUG ("Could not find a source for %s",
                 GRL_METADATA_KEY_GET_NAME (key));
    }
  }


  return list_union (NULL, result, NULL);
}
