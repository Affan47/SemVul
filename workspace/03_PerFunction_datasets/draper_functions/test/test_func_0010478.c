parse_IEEE1284_to_model (char *scanner_id, char *model)
{


  char s[BJNP_IEEE1284_MAX];
  char *tok;

  strcpy (s, scanner_id);
  model[0] = '\0';

  tok = strtok (s, ";");
  while (tok != NULL)
    {


      if (strncmp (tok, "DES:", 4) == 0)
	{
	  strcpy (model, tok + 4);
	  return 1;
	}
      tok = strtok (NULL, ";");
    }
  return 0;
}
