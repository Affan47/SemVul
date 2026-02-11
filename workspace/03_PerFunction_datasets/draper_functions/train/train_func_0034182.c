gagt_find_paragraph_start (const gagt_lineref_t begin)
{
  gagt_lineref_t line, match;


  match = NULL;
  for (line = begin; line; line = gagt_get_next_page_line (line))
    {
      if (!line->is_blank)
        {
          match = line;
          break;
        }
    }

  return match;
}
