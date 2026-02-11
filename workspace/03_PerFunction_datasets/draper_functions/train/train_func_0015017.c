add_section_from_token( struct parser *parser )
{
  PINFCACHESECTION Section;

  if (parser->token_len > MAX_SECTION_NAME_LEN)
    {
      parser->error = INF_STATUS_SECTION_NAME_TOO_LONG;
      return NULL;
    }

  Section = InfpFindSection(parser->file,
                            parser->token);
  if (Section == NULL)
    {

      Section= InfpAddSection(parser->file,
                              parser->token);
      if (Section == NULL)
        {
          parser->error = INF_STATUS_NOT_ENOUGH_MEMORY;
          return NULL;
        }
    }

  parser->token_len = 0;
  parser->cur_section = Section;

  return (PVOID)Section;
}
