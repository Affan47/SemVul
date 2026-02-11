add_content (const char *sectname, char *line, int verbatim)
{
  section_buffer_t sect;
  line_buffer_t lb;

  sect = get_section_buffer (sectname);
  if (sect->last_line && !sect->last_line->verbatim == !verbatim)
    {


      size_t n1, n;

      lb = sect->last_line;
      n1 = strlen (lb->line);
      n = n1 + 1 + strlen (line) + 1;
      lb->line = xrealloc (lb->line, n);
      strcpy (lb->line+n1, "\n");
      strcpy (lb->line+n1+1, line);
    }
  else
    {
      lb = xcalloc (1, sizeof *lb);
      lb->verbatim = verbatim;
      lb->line = xstrdup (line);
      sect->last_line = lb;
      *sect->lines_tail = lb;
      sect->lines_tail = &lb->next;
    }
}
