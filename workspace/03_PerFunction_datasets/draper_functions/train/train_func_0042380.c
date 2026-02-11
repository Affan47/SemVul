unicode_char_to_zscii_input_char(z_ucs unicode_char)
{
  zscii result;

  if (unicode_char == 8)
    result = 8;
  else if (unicode_char == 10)
    result = 13;
  else if (unicode_char == 13)
    result = 13;
  else if (unicode_char == 27)
    result = 27;
  else if ((unicode_char >= 32) && (unicode_char <= 126))
    result = (uint8_t)unicode_char;
  else
  {


    result = find_zscii_extra_char_in_unicode_table(unicode_char);
  }

  return result;
}
