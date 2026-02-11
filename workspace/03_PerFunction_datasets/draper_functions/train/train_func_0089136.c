free_option_group (gpointer data)
{
  XkbOptionGroup *group = data;

  g_return_if_fail (group != NULL);

  g_free (group->id);
  g_free (group->description);
  g_hash_table_destroy (group->options_table);
  g_slice_free (XkbOptionGroup, group);
}
