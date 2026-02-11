get_year_value(THD *thd, Item ***item_arg, Item **cache_arg,
               Item *warn_item, bool *is_null)
{
  longlong value= 0;
  Item *item= **item_arg;

  value= item->val_int();
  *is_null= item->null_value;
  if (*is_null)
    return ~(ulonglong) 0;


  Item *real_item= item->real_item();
  Field *field= NULL;
  if (real_item->type() == Item::FIELD_ITEM)
    field= ((Item_field *)real_item)->field;
  else if (real_item->type() == Item::CACHE_ITEM)
    field= ((Item_cache *)real_item)->field();
  if (!(field && field->type() == MYSQL_TYPE_YEAR && field->field_length == 4))
  {
    if (value < 70)
      value+= 100;
    if (value <= 1900)
      value+= 1900;
  }

  value*= 10000000000LL;

  return value;
}
