sb_remove_some_space(String_buf sb, int begin, int end)
{
  int i;
  BOOL in_quote = FALSE;
  for (i = begin; i < end-1; i++) {
    char c = sb_char(sb, i);
    if (quote_char(c))
      in_quote = !in_quote;
    else if (!in_quote && sb_char(sb, i) == ' ') {
      if (sb_char(sb, i-1) == '-') {
	if (!special_char(sb_char(sb, i-2)))
	  sb_replace_char(sb, i, '\0');
      }
      else if (sb_char(sb, i+1) == '\'') {
	if (!special_char(sb_char(sb, i+2)))
	  sb_replace_char(sb, i, '\0');
      }
    }
  }
}
