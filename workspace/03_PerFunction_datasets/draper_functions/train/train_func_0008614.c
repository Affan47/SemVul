getAttr (attrName)
     char *attrName;
{
  int i;

  for (i = 0; atStdAttrTab[i].name; i++) {
    if (!(strcmp (attrName, atStdAttrTab[i].name)))
      return (atStdAttrTab[i].code);
  }
  return (-1);
}
