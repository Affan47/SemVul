log_store_pidgin_search_hit_new (TplLogStore *self,
    const gchar *filename)
{
  TplLogSearchHit *hit;
  gchar **strv;
  guint len;
  TplEntityType type;
  gchar *id;

  if (!g_str_has_suffix (filename, TXT_LOG_FILENAME_SUFFIX)
      && !g_str_has_suffix (filename, HTML_LOG_FILENAME_SUFFIX))
    return NULL;

  strv = g_strsplit (filename, G_DIR_SEPARATOR_S, -1);
  len = g_strv_length (strv);

  hit = g_slice_new0 (TplLogSearchHit);
  hit->date = log_store_pidgin_get_time (strv[len-1]);

  type = g_str_has_suffix (strv[len-2], ".chat")
    ? TPL_ENTITY_ROOM : TPL_ENTITY_CONTACT;


  if (type == TPL_ENTITY_ROOM)
    id = g_strndup (strv[len-2], (strlen (strv[len-2]) - 5));
  else
    id = g_strdup (strv[len-2]);

  hit->target = tpl_entity_new (id, type, NULL, NULL);

  g_free (id);

  hit->account = log_store_pidgin_dup_account (filename);

  g_strfreev (strv);

  return hit;
}
