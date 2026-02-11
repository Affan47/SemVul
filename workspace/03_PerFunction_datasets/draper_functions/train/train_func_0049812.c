fix_length_and_dec()
{
  ulonglong char_length= (ulonglong) args[0]->max_char_length();
  int diff=(int) (args[2]->max_char_length() - args[1]->max_char_length());
  if (diff > 0 && args[1]->max_char_length())
  {
    ulonglong max_substrs= char_length / args[1]->max_char_length();
    char_length+= max_substrs * (uint) diff;
  }

  if (agg_arg_charsets_for_string_result_with_comparison(collation, args, 3))
    return;
  fix_char_length_ulonglong(char_length);
}
