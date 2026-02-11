gconf_source_unset_value      (GConfSource* source,
                               const gchar* key,
                               const gchar* locale,
                               GError** err)
{
  g_return_val_if_fail (source != NULL, FALSE);
  g_return_val_if_fail (key != NULL, FALSE);
  g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

  if ( source_is_writable(source, key, err) )
    {
      g_return_val_if_fail(err == NULL || *err == NULL, FALSE);

      (*source->backend->vtable.unset_value)(source, key, locale, err);
      return TRUE;
    }
  else
    return FALSE;
}
