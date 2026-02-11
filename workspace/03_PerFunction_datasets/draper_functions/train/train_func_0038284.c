fix_length_and_dec()
{
  Item_num_op::fix_length_and_dec();
  if (unsigned_flag &&
      (current_thd->variables.sql_mode & MODE_NO_UNSIGNED_SUBTRACTION))
    unsigned_flag=0;
}
