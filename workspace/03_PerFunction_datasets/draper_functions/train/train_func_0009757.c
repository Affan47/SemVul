openload_ruleset_file(const char *whichset)
{
  char sfilename[512];
  const char *dfilename = valid_ruleset_filename(game.server.rulesetdir,
                                                 whichset, RULES_SUFFIX);
  struct section_file *secfile;


  sz_strlcpy(sfilename, dfilename);

  if (!(secfile = secfile_load(sfilename, FALSE))) {
    ruleset_error(LOG_FATAL, "Could not load ruleset '%s':\n%s",
                  sfilename, secfile_error());
  }
  return secfile;
}
