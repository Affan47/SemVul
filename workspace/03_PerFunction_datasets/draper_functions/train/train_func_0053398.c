val_int()
{
  longlong value;
  int error;

  if (args[0]->cast_to_int_type() == DECIMAL_RESULT)
  {
    my_decimal tmp, *dec= args[0]->val_decimal(&tmp);
    if (!(null_value= args[0]->null_value))
      my_decimal2int(E_DEC_FATAL_ERROR, dec, 1, &value);
    else
      value= 0;
    return value;
  }
  else if (args[0]->cast_to_int_type() != STRING_RESULT ||
           args[0]->result_as_longlong())
  {
    value= args[0]->val_int();
    null_value= args[0]->null_value;
    return value;
  }

  value= val_int_from_str(&error);
  if (error < 0)
    push_warning(current_thd, MYSQL_ERROR::WARN_LEVEL_WARN, ER_UNKNOWN_ERROR,
                 "Cast to unsigned converted negative integer to it's "
                 "positive complement");
  return value;
}
