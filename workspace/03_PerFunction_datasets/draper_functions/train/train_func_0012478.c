html_span(char *class, char *text)
{
  char *s;

  if (text == NULL)
    s = ds_xprintf("<span class=\"%s\">", class);
  else
    s = ds_xprintf("<span class=\"%s\">%s</span>", class, text);

  return(s);
}
