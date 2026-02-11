factory(const std::string &fn, Copl *opl, const CPlayers &pl,
			  const CFileProvider &fp)
{
  CPlayer			*p;
  CPlayers::const_iterator	i;
  unsigned int			j;

  AdPlug_LogWrite("*** CAdPlug::factory(\"%s\",opl,fp) ***\n", fn.c_str());


  for(i = pl.begin(); i != pl.end(); i++)
    for(j = 0; (*i)->get_extension(j); j++)
      if(fp.extension(fn, (*i)->get_extension(j))) {
	AdPlug_LogWrite("Trying direct hit: %s\n", (*i)->filetype.c_str());
	if((p = (*i)->factory(opl))) {
	  if(p->load(fn, fp)) {
	    AdPlug_LogWrite("got it!\n");
	    AdPlug_LogWrite("--- CAdPlug::factory ---\n");
	    return p;
	  } else
	    delete p;
	}
      }


  for(i = pl.begin(); i != pl.end(); i++) {
    AdPlug_LogWrite("Trying: %s\n", (*i)->filetype.c_str());
    if((p = (*i)->factory(opl))) {
      if(p->load(fn, fp)) {
        AdPlug_LogWrite("got it!\n");
        AdPlug_LogWrite("--- CAdPlug::factory ---\n");
	return p;
      } else
	delete p;
    }
  }


  AdPlug_LogWrite("End of list!\n");
  AdPlug_LogWrite("--- CAdPlug::factory ---\n");
  return 0;
}
