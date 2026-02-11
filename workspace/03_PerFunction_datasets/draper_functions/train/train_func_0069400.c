agg_str_lengths(Item* arg)
{
  fix_char_length(max(max_char_length(), arg->max_char_length()));
  set_if_bigger(decimals, arg->decimals);
  unsigned_flag= unsigned_flag && arg->unsigned_flag;
}
