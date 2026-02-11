alias_expand_token (tokstr)
     char *tokstr;
{
  char *expanded;
  alias_t *ap;

  if (((parser_state & PST_ALEXPNEXT) || command_token_position (last_read_token)) &&
	(parser_state & PST_CASEPAT) == 0)
    {
      ap = find_alias (tokstr);


      if (ap && (ap->flags & AL_BEINGEXPANDED))
	return (NO_EXPANSION);


      expanded = ap ? mk_alexpansion (ap->value) : (char *)NULL;

      if (expanded)
	{
	  push_string (expanded, ap->flags & AL_EXPANDNEXT, ap);
	  return (RE_READ_TOKEN);
	}
      else

	return (NO_EXPANSION);
    }
  return (NO_EXPANSION);
}
