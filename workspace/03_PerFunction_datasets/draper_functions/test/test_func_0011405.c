forget_multiple_char_special_syms(char *str)
{


  if (special_char(*str) &&
      strlen(str) > 1 &&
      string_member_plist(str, Multiple_char_special_syms)) {
    Multiple_char_special_syms =
      plist_remove_string(Multiple_char_special_syms, str);
  }
}
