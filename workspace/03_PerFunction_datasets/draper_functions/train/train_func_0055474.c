handle_stdc_pragma (const char *pname)
{
  const char *arg;
  tree t;
  enum pragma_switch_t ret;

  if (!valid_location_for_stdc_pragma_p ())
    {
      warning (OPT_Wpragmas, "invalid location for %<pragma %s%>, ignored",
	       pname);
      return PRAGMA_BAD;
    }

  if (pragma_lex (&t) != CPP_NAME)
    {
      warning (OPT_Wpragmas, "malformed %<#pragma %s%>, ignored", pname);
      return PRAGMA_BAD;
    }

  arg = IDENTIFIER_POINTER (t);

  if (!strcmp (arg, "ON"))
    ret = PRAGMA_ON;
  else if (!strcmp (arg, "OFF"))
    ret = PRAGMA_OFF;
  else if (!strcmp (arg, "DEFAULT"))
    ret = PRAGMA_DEFAULT;
  else
    {
      warning (OPT_Wpragmas, "malformed %<#pragma %s%>, ignored", pname);
      return PRAGMA_BAD;
    }

  if (pragma_lex (&t) != CPP_EOF)
    {
      warning (OPT_Wpragmas, "junk at end of %<#pragma %s%>", pname);
      return PRAGMA_BAD;
    }

  return ret;
}
