read_color (const gchar * line, gint * r, gint * g, gint * b)
{
  gint index = 0;
  while (line[index] != ':' && line[index] != '}') {
    index++;
  }
  if (line[index] != ':')
    return FALSE;
  index++;

  *r = atoi (line + index);

  while (line[index] != '}' && line[index] != ',') {
    index++;
  }
  if (line[index] != ',')
    return FALSE;
  index++;

  *g = atoi (line + index);

  while (line[index] != '}' && line[index] != ',') {
    index++;
  }
  if (line[index] != ',')
    return FALSE;
  index++;

  *b = atoi (line + index);

  return TRUE;
}
