fix_fields(THD *thd, Item **ref)
{
  DBUG_ASSERT(fixed == 0);
  if (fix_left(thd, ref))
    return TRUE;
  if (args[0]->maybe_null)
    maybe_null=1;

  if (!args[1]->fixed && args[1]->fix_fields(thd, args+1))
    return TRUE;
  Item_in_subselect * sub= (Item_in_subselect *)args[1];
  if (args[0]->cols() != sub->engine->cols())
  {
    my_error(ER_OPERAND_COLUMNS, MYF(0), args[0]->cols());
    return TRUE;
  }
  if (args[1]->maybe_null)
    maybe_null=1;
  with_sum_func= with_sum_func || args[1]->with_sum_func;
  used_tables_cache|= args[1]->used_tables();
  not_null_tables_cache|= args[1]->not_null_tables();
  const_item_cache&= args[1]->const_item();
  fixed= 1;
  return FALSE;
}
