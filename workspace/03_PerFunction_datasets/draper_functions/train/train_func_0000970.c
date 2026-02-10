atk_table_get_index_at (AtkTable *table,
                        gint     row,
                        gint     column)
{
  AtkTableIface *iface;

  g_return_val_if_fail (ATK_IS_TABLE (table), -1);
  g_return_val_if_fail (row >= 0, -1);
  g_return_val_if_fail (column >= 0, -1);

  iface = ATK_TABLE_GET_IFACE (table);

  if (iface->get_index_at)
    return (iface->get_index_at) (table, row, column);
  else
    return -1;
}
