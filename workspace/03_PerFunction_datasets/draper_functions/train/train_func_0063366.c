hack_special_boolean_var (i)
     int i;
{
  const char *name;

  name = boolean_varlist[i].name;

  if (_rl_stricmp (name, "blink-matching-paren") == 0)
    _rl_enable_paren_matching (rl_blink_matching_paren);
  else if (_rl_stricmp (name, "prefer-visible-bell") == 0)
    {
      if (_rl_prefer_visible_bell)
	_rl_bell_preference = VISIBLE_BELL;
      else
	_rl_bell_preference = AUDIBLE_BELL;
    }
}
