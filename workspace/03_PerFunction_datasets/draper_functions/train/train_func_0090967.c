forward_to_next_token_char (const char *ptr)
{
  for (++ptr; ISSPACE ((const unsigned char)*ptr);
       check_source (++ptr < clean_text_limit, 0))
    continue;
  return ptr;
}
