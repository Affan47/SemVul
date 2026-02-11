get_entity (const unsigned char *string, int length)
{
  int i;
  unsigned char c = *string;
  for (i = 0; i < (sizeof(entities)/sizeof(*entities)); i++)
    if (length == entities[i].length &&
	c == entities[i].string[0] &&
	!strncmp(string, entities[i].string, length))
      return entities[i].latin1_char;
  return 0;
}
