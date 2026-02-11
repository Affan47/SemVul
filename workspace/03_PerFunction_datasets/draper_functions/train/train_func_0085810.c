get_comparator(Item_result type,
                                   CHARSET_INFO *cs)
{
  switch (type) {
  case STRING_RESULT:
    return new cmp_item_sort_string(cs);
  case INT_RESULT:
    return new cmp_item_int;
  case REAL_RESULT:
    return new cmp_item_real;
  case ROW_RESULT:
    return new cmp_item_row;
  case DECIMAL_RESULT:
    return new cmp_item_decimal;
  default:
    DBUG_ASSERT(0);
    break;
  }
  return 0;
}
