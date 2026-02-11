next_is_type_keyword()
{
  static char peek_buffer[emf_MAX_STRING_LEN];

  if ( !peek_token(peek_buffer) )
    return false;

  LibFront::toLower(peek_buffer);

  if ( is_type_keyword(peek_buffer) )
    return true;
  else
    return false;
}
