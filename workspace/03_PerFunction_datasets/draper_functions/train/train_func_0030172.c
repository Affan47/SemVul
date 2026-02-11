set_schema (GConfSource *source,
            const char  *key,
            const char  *schema_name,
            GError     **err)
{
  MarkupSource* ms = (MarkupSource*)source;
  MarkupEntry *entry;
  GError *tmp_err;

  g_return_if_fail (key != NULL);
  g_return_if_fail (source != NULL);


  tmp_err = NULL;
  entry = tree_lookup_entry (ms->tree,
                             key, TRUE, &tmp_err);
  if (tmp_err != NULL)
    {
      g_propagate_error (err, tmp_err);
      return;
    }

  g_return_if_fail (entry != NULL);

  markup_entry_set_schema_name (entry, schema_name);
}
