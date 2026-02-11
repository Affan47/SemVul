fix_length_and_dec()
{
  agg_arg_charsets_for_string_result(collation, args, 1);
  DBUG_ASSERT(collation.collation != NULL);
  left_right_max_length();
}
