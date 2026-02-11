cm_gdata_query_groups_ready(GDataContactsService *service, GAsyncResult *res, gpointer data)
{
  GDataFeed *feed;
  GList *walk;
  GError *error = NULL;

  feed = gdata_service_query_finish(GDATA_SERVICE(service), res, &error);
  if(error)
  {
    g_object_unref(feed);
    log_error(LOG_PROTOCOL, _("GData plugin: Error querying for groups: %s\n"), error->message);
    g_error_free(error);
    return;
  }


  for(walk = gdata_feed_get_entries(feed); walk; walk = walk->next) {
    const gchar *system_group_id;
    GDataContactsGroup *group = GDATA_CONTACTS_GROUP(walk->data);

    system_group_id = gdata_contacts_group_get_system_group_id(group);
    if(system_group_id && !strcmp(system_group_id, GDATA_CONTACTS_GROUP_CONTACTS)) {
      gchar *pos;
      const gchar *id;

      id = gdata_entry_get_id(GDATA_ENTRY(group));


      pos = g_strrstr(id, "/full/");
      if(pos) {
        GString *str = g_string_new("\0");
        int off = pos-id;

        g_string_append_len(str, id, off);
        g_string_append(str, "/base/");
        g_string_append(str, id+off+strlen("/full/"));
        g_string_append_c(str, '\0');
        contacts_group_id = str->str;
        g_string_free(str, FALSE);
      }
      else
        contacts_group_id = g_strdup(id);
      break;
    }
  }
  g_object_unref(feed);

  log_message(LOG_PROTOCOL, _("GData plugin: Groups received\n"));

  query_after_auth(service);
}
