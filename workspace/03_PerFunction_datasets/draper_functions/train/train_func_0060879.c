reset()
{
  DBUG_ENTER("Item_param::reset");

  if (str_value.alloced_length() > MAX_CHAR_WIDTH)
    str_value.free();
  else
    str_value.length(0);
  str_value_ptr.length(0);


  str_value.set_charset(&my_charset_bin);
  collation.set(&my_charset_bin, DERIVATION_COERCIBLE);
  state= NO_VALUE;
  maybe_null= 1;
  null_value= 0;


  DBUG_VOID_RETURN;
}
