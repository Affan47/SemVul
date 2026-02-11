quotes_state( struct parser *parser, const WCHAR *pos )
{
  const WCHAR *p, *token_end = parser->start;

  for (p = pos; !is_eol( parser, p ); p++)
    {
      if (*p == '"')
        {
          if (p+1 < parser->end && p[1] == '"')
            {
              push_token( parser, p + 1 );
              parser->start = token_end = p + 2;
              p++;
            }
          else
            {
              push_token( parser, p );
              parser->start = p + 1;
              pop_state( parser );
              return p + 1;
            }
        }
    }
  push_token( parser, p );
  pop_state( parser );
  return p;
}
