load_item_from_keyfile (SwService  *service,
                        GKeyFile   *keyfile,
                        const char *group)
{
  SwCacheable *cacheable = NULL;
  char **keys;
  gsize i, count;

  keys = g_key_file_get_keys (keyfile, group, &count, NULL);
  if (keys) {
    const gchar *type = g_key_file_get_string (keyfile, group, "type",
        NULL);

    if (!type || g_str_equal (type, "item")) {
      cacheable = SW_CACHEABLE (sw_item_new ());
      sw_item_set_service (SW_ITEM (cacheable), service);
      for (i = 0; i < count; i++) {
        char *value, *new_value;

        value = g_key_file_get_string (keyfile, group, keys[i], NULL);


        new_value = make_absolute_path (keys[i], value);

        if (new_value) {
          sw_item_take (SW_ITEM (cacheable), keys[i], new_value);
          g_free (value);
        } else {
          sw_item_take (SW_ITEM (cacheable), keys[i], value);
        }
      }
    } else if (g_str_equal (type, "contact")) {
      cacheable = SW_CACHEABLE (sw_contact_new ());
      sw_contact_set_service (SW_CONTACT (cacheable), service);
      for (i = 0; i < count; i++) {
        char **str_array;
        int j;

        str_array = g_key_file_get_string_list (keyfile, group, keys[i], NULL,
            NULL);
        for (j = 0 ; str_array && str_array[j] ; j++) {
          sw_contact_put (SW_CONTACT (cacheable), keys[i], str_array[j]);
        }
        g_strfreev (str_array);
      }
    }
  }

  g_strfreev (keys);

  if (cacheable && sw_service_is_uid_banned (service,
        sw_cacheable_get_id (cacheable)))
  {
    g_object_unref (cacheable);

    return NULL;
  }

  return cacheable;
}
