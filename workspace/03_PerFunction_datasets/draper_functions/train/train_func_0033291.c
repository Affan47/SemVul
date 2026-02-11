rcoxml_text_to_int (char *s, const RcoTableMap map, uint32_t * out)
{
  if (!s[0])
    return FALSE;

  int i = 0;

  while (map[i][0]) {
    if (!strcasecmp (map[i], s)) {
      *out = (uint32_t) i;
      return TRUE;
    }
    i++;
  }


  return (sscanf (s, "unknown%i", out) == 1);
}
