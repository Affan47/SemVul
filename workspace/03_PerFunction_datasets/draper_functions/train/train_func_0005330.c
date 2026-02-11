set_expect_flag (Expect_flag& flag, const char* value_str)
{
  sstring value (value_str);
  value.to_lower();
  if (value == sstring("yes") || value == sstring("y")) flag = YES;
  else if (value == sstring("no") || value == sstring("n")) flag = NO;
  else if (value == sstring("auto") || value == sstring("a")) flag = AUTO;
  else THROW Syntax_exception (*this, "expected 'yes', 'no' or 'auto'");
}
