get_charset_number_internal(const char *charset_name, uint cs_flags)
{
  CHARSET_INFO **cs;

  for (cs= all_charsets;
       cs < all_charsets + array_elements(all_charsets);
       cs++)
  {
    if ( cs[0] && cs[0]->csname && (cs[0]->state & cs_flags) &&
         !my_strcasecmp(&my_charset_latin1, cs[0]->csname, charset_name))
      return cs[0]->number;
  }
  return 0;
}
