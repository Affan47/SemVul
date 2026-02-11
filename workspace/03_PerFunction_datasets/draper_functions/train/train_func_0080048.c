init_parse_line(char *line_to_parse)
{

  lineptr = (unsigned char *)line_to_parse;
  char *nl;
  if ((nl = strchr(line_to_parse,'\n')) != NULL) {
    *nl = 0;
  }
}
