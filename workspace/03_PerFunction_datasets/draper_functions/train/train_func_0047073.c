parseQueryFormat (const DatabaseInfo database, const char *expr,
		  ErrorDesc *err)
{
  const char *sstart;
  char *fstring = NULL;
  QueryFormat *res;
  FieldList currEnt = NULL;

  while (expr[0] != '\0' && isspace ((int)(unsigned char) expr[0]))
    {
      expr++;
    }
  if (expr[0] == '\0')
    {
      return NULL;
    }
  if (expr[0] == '"')
    {
      expr++;
      sstart = expr;

      while (expr[0] != '\0' && expr[0] != '\"')
	{
	  if (expr[0] == '\\' && expr[1] != '\0')
	    {
	      expr++;
	    }
	  expr++;
	}

      fstring = xmalloc (expr - sstart + 1);
      memcpy (fstring, sstart, expr - sstart);
      fstring[expr - sstart] = '\0';
      if (expr[0] == '"')
	{
	  expr++;
	}
    }
  res = (QueryFormat *) xmalloc (sizeof (QueryFormat));
  res->name = NULL;
  res->printf = fstring;
  res->separator = xstrdup ("\n");
  res->fields = NULL;
  while (expr[0] != '\0')
    {
      const char *nstart = expr;
      FieldList newEnt;

      if (isspace ((int)(unsigned char) expr[0]))
	{
	  expr++;
	  continue;
	}
      while ((! isspace ((int)(unsigned char) expr[0])) && expr[0] != '\0')
	{
	  expr++;
	}
      fstring = xmalloc (expr - nstart + 1);
      memcpy (fstring, nstart, expr - nstart);
      fstring[expr - nstart] = '\0';
      newEnt = newFieldListEnt (database, fstring, NULL);
      if (currEnt == NULL)
	{
	  res->fields = newEnt;
	}
      else
	{
	  currEnt->next = newEnt;
	}
      currEnt = newEnt;
      if (parseComplexFieldIndex (currEnt->ent) != 0)
	{
	  setError (err, CODE_INVALID_FIELD_NAME,
		    "Invalid field name or query format %s", fstring);
	  freeQueryFormat (res);
	  res = NULL;
	  break;
	}
    }
  return res;
}
