toolbars_item_new (const char *id,
		   const char *type,
		   gboolean    separator)
{
  EggToolbarsItem *item;

  g_return_val_if_fail (id != NULL, NULL);
  g_return_val_if_fail (type != NULL, NULL);

  item = g_new (EggToolbarsItem, 1);
  item->id = g_strdup (id);
  item->type = g_strdup (type);
  item->separator = separator;

  return item;
}
