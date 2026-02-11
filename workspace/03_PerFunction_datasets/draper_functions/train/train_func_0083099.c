val_str(String *str)
{

  DBUG_ASSERT(fixed == 1);
  str->set_real(value,decimals,&my_charset_bin);
  return str;
}
