fix_fields(THD *thd, Item **ref)
{
  List_iterator_fast<Item_field> li(fields);
  Item *item;
  not_null_tables_cache= used_tables_cache= 0;
  const_item_cache= 0;
  while ((item= li++))
  {
    table_map tmp_table_map;
    used_tables_cache|= item->used_tables();
    tmp_table_map= item->not_null_tables();
    not_null_tables_cache|= tmp_table_map;
    if (item->maybe_null)
      maybe_null=1;
  }
  fix_length_and_dec();
  fixed= 1;
  return 0;
}
