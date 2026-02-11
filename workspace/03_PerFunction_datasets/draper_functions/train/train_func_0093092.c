peas_extension_set_get_extension (PeasExtensionSet *set,
                                  PeasPluginInfo   *info)
{
  GList *l;

  g_return_val_if_fail (PEAS_IS_EXTENSION_SET (set), NULL);
  g_return_val_if_fail (info != NULL, NULL);

  for (l = set->priv->extensions; l != NULL; l = l->next)
    {
      ExtensionItem *item = l->data;

      if (item->info == info)
        return item->exten;
    }

  return NULL;
}
