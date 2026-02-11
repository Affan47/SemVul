handle_get (GVfsMetadata *object,
            GDBusMethodInvocation *invocation,
            const gchar *arg_treefile,
            const gchar *arg_path,
            const gchar *const *arg_keys,
            GVfsMetadata *daemon)
{
  TreeInfo *info;
  GPtrArray *meta_keys;
  gboolean free_keys;
  gchar **iter_keys;
  gchar **i;
  GVariantBuilder *builder;

  info = tree_info_lookup (arg_treefile);
  if (info == NULL)
    {
      g_dbus_method_invocation_return_error (invocation,
                                             G_IO_ERROR,
                                             G_IO_ERROR_NOT_FOUND,
                                             _("Can't find metadata file %s"),
                                             arg_treefile);
      return TRUE;
    }

  if (arg_keys == NULL)
    {

      free_keys = TRUE;
      meta_keys = g_ptr_array_new ();
      meta_tree_enumerate_keys (info->tree, arg_path, enum_keys, meta_keys);
      iter_keys = (gchar **) g_ptr_array_free (meta_keys, FALSE);
    }
  else
    {
      free_keys = FALSE;
      iter_keys = (gchar **) arg_keys;
    }

  builder = g_variant_builder_new (G_VARIANT_TYPE_VARDICT);

  for (i = iter_keys; *i; i++)
    append_key (builder, info->tree, arg_path, *i);
  if (free_keys)
    g_strfreev (iter_keys);

  gvfs_metadata_complete_get (object, invocation,
                              g_variant_builder_end (builder));
  g_variant_builder_unref (builder);

  return TRUE;
}
