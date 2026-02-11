cmp(void)
{
  String *res;
  bool tmp;

  if ((res=item->val_str(&tmp_value)))
    res->length(min(res->length(), value_max_length));
  if (null_value != item->null_value)
  {
    if ((null_value= item->null_value))
      return TRUE;
    tmp=TRUE;
  }
  else if (null_value)
    return 0;
  else
    tmp= sortcmp(&value,res,item->collation.collation) != 0;
  if (tmp)
    value.copy(*res);
  return tmp;
}
