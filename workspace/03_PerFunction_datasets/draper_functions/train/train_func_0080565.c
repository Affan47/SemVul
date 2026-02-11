is_radix_char (LINE_T ** ref_l, char **ref_s, char *ch)
{
  BOOL_T ret = A68_FALSE;
  save_state (*ref_l, *ref_s, *ch);
  if (OPTION_STROPPING (&program) == QUOTE_STROPPING) {
    if (*ch == TO_UPPER (RADIX_CHAR)) {
      *ch = next_char (ref_l, ref_s, A68_TRUE);
      ret = (BOOL_T) (strchr ("0123456789ABCDEF", *ch) != NO_TEXT);
    }
  } else {
    if (*ch == RADIX_CHAR) {
      *ch = next_char (ref_l, ref_s, A68_TRUE);
      ret = (BOOL_T) (strchr ("0123456789abcdef", *ch) != NO_TEXT);
    }
  }
  restore_state (ref_l, ref_s, ch);
  return (ret);
}
