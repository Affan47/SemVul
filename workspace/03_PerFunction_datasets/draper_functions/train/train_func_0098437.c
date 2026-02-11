_ds_pref_val(
  agent_pref_t PTX,
  const char *attrib)
{
  agent_attrib_t pref;
  int i;

  if (PTX == NULL)
    return "";

  for(i=0;PTX[i];i++) {
    pref = PTX[i];
    if (!strcasecmp(pref->attribute, attrib))
      return pref->value;
  }

  return "";
}
