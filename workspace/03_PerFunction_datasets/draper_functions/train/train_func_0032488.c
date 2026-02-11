meta_table_column_is_primary_key(GdaMetaTable* meta_table, const Glib::ustring column_name)
{
  if(!meta_table)
    return false;

  for(GSList* item = meta_table->columns; item != 0; item = item->next)
  {
    GdaMetaTableColumn* column = GDA_META_TABLE_COLUMN(item->data);
    if(!column)
      continue;

    if(column->column_name && (column_name == remove_quotes(column->column_name)))
      return column->pkey;
  }

  return false;
}
