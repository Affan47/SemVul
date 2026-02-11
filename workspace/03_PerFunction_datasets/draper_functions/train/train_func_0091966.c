fix_fields(THD *thd, Item **ref)
{
  DBUG_ASSERT(fixed == 0);

  Item *item= args[0];

  if (init_sum_func_check(thd))
    return TRUE;


  if ((!item->fixed && item->fix_fields(thd, args)) ||
      (item= args[0])->check_cols(1))
    return TRUE;
  decimals=item->decimals;

  switch (hybrid_type= item->result_type()) {
  case INT_RESULT:
  case DECIMAL_RESULT:
  case STRING_RESULT:
    max_length= item->max_length;
    break;
  case REAL_RESULT:
    max_length= float_length(decimals);
    break;
  case ROW_RESULT:
  default:
    DBUG_ASSERT(0);
  };
  setup_hybrid(args[0], NULL);

  maybe_null= 1;
  unsigned_flag=item->unsigned_flag;
  result_field=0;
  null_value=1;
  fix_length_and_dec();
  item= item->real_item();
  if (item->type() == Item::FIELD_ITEM)
    hybrid_field_type= ((Item_field*) item)->field->type();
  else
    hybrid_field_type= Item::field_type();

  if (check_sum_func(thd, ref))
    return TRUE;

  orig_args[0]= args[0];
  fixed= 1;
  return FALSE;
}
