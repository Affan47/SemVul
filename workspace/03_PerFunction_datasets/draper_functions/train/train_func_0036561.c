create_result_table(THD *thd_arg, List<Item> *column_types,
                                  bool is_union_distinct, ulonglong options,
                                  const char *alias)
{
  DBUG_ASSERT(table == 0);
  tmp_table_param.init();
  tmp_table_param.field_count= column_types->elements;

  if (! (table= create_tmp_table(thd_arg, &tmp_table_param, *column_types,
                                 (ORDER*) 0, is_union_distinct, 1,
                                 options, HA_POS_ERROR, alias)))
    return TRUE;
  table->file->extra(HA_EXTRA_WRITE_CACHE);
  table->file->extra(HA_EXTRA_IGNORE_DUP_KEY);
  return FALSE;
}
