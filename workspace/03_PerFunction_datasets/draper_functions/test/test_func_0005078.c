ar_conf_get_integer_list (const char *group, const char *key,
                             gsize * n_values, GError ** error)
{
  ArConfPrivate *priv = instance->priv;

#ifdef HAVE_GNOME
  char *key_name;
  GSList *list, *l;
  int *values = NULL;
  gsize n = 0;

  key_name = get_gconf_key_name (group, key);

  list = gconf_client_get_list (priv->gconf_client, key_name, GCONF_VALUE_STRING, NULL);
  if (list != NULL) {
    values = g_new (int, g_slist_length (list));

    for (l = list; l != NULL; l = l->next) {
      values[n++] = GPOINTER_TO_INT (l->data);
    }
  }

  *n_values = n;

  g_free (key_name);
  return values;
#else
  return g_key_file_get_integer_list (priv->key_file, group ? group : priv->main_group, key, n_values, error);
#endif
}
