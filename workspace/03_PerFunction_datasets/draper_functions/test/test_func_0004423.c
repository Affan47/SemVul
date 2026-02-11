val_str(String *str)
{
  DBUG_ASSERT(fixed == 1);
  String *res= args[0]->val_str(str);

  longlong length= args[1]->val_int();

  if ((null_value=(args[0]->null_value || args[1]->null_value)))
    return 0;


  if ((length <= 0) && (!args[1]->unsigned_flag))
    return make_empty_result();

  if (res->length() <= (ulonglong) length)
    return res;

  uint start=res->numchars();
  if (start <= (uint) length)
    return res;
  start=res->charpos(start - (uint) length);
  tmp_value.set(*res,start,res->length()-start);
  return &tmp_value;
}
