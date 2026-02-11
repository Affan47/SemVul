hashkit_string_append_character(hashkit_string_st *string,
                                     char character)
{
  if (_string_check(string, 1) == false)
  {
    return false;
  }

  *string->end= character;
  string->end++;

  return true;
}
