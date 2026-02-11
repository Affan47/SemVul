attribute_name_to_id(char *name)
{
  int i;
  for (i = 0; i < MAX_ATTRIBUTE_NAMES; i++) {
    if (Attribute_names[i].name != NULL &&
	str_ident(Attribute_names[i].name, name))
      return i;
  }
  return -1;
}
