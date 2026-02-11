hs_parse_tag(hs, text, len)
MLState hs;
char *text;
size_t len;
{
  char *cp, *start, *lastcp;
  MLAttribute tahead, tatail, ta;
  size_t newlen;

  tahead = NULL;
  tatail = NULL;
  lastcp = text + len;
  for (cp = text; cp < lastcp; )
  {

    for (; cp < lastcp && isspace8(*cp); cp++)
	;
    if (cp == lastcp) break;


    for (start = cp; cp < lastcp && !isspace8(*cp) && *cp != '='; cp++)
	;

    ta = hs_create_attribute(hs, start, cp - start);

    if (isspace8(*cp))
    {
      for (; cp < lastcp && isspace8(*cp); cp++)
	  ;
    }


    if (cp < lastcp && *cp == '=')
    {
      cp++;


      for (; cp < lastcp && isspace8(*cp); cp++)
	  ;
      if (cp < lastcp)
      {

	if (*cp == '"')
	{
	  cp++;

	  for (start = cp; cp < lastcp && *cp != '"'; cp++)
	      ;
	}
	else if (*cp == '\'')
	{
	  cp++;

	  for (start = cp; cp < lastcp && *cp != '\''; cp++)
	      ;
	}
	else
	{
	  for (start = cp; cp < lastcp && !isspace8(*cp); cp++)
	      ;
	}

	ta->value = hs_condense(hs, start, cp - start, &newlen);
      }
    }

    if (tatail == NULL) tahead = ta;
    else tatail->next = ta;
    tatail = ta;
  }

  return(tahead);
}
