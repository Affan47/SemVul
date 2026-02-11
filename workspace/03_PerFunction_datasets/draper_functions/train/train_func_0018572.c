decodeRdnParam (
	char	*value)
{
  int	 i;


  mctx.object.rdn      = (vers_attribute *) malloc (sizeof (vers_attribute));
  mctx.object.rdn->buf = NULL;


  for (i=0 ; (value[i] != '\0') && (value[i] != ':') ; i++);
  if (value[i] == '\0')
  {
    fprintf (stderr, "Error: missing rdn attribute name\n");
    return (-1);
  }
  mctx.object.rdnName = (char *) malloc (i+1);
  strncpy (mctx.object.rdnName, value, i);
  mctx.object.rdnName[i] = '\0';


  if (parseAttribValue ("-e rdn=", &(mctx.object),
				value+i+1, mctx.object.rdn) < 0)
    return (-1);

  return (0);
}
