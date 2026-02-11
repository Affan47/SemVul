logDefaultArgumentLocations(void)
{
  std::list<std::string>::iterator it;
  std::list<bool>::iterator bIt;

  ArLog::log(ArLog::Normal,
	     "Default argument files or environmental variables:");
  for (it = ourDefaultArgumentLocs.begin(),
        bIt = ourDefaultArgumentLocIsFile.begin();
       it != ourDefaultArgumentLocs.end();
       it++, bIt++)
  {
    if (*bIt)
      ArLog::log(ArLog::Normal, "%10s%-10s%s", "", "file", (*it).c_str());
    else
      ArLog::log(ArLog::Normal, "%10s%-10s%s", "", "envVar", (*it).c_str());
  }
}
