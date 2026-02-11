copySectionsToParse(std::list<std::string> *from)
{

  if (mySectionsToParse != NULL)
    delete mySectionsToParse;
  std::string sections;
  mySectionsToParse = NULL;
  if (from != NULL) {
    mySectionsToParse = new std::list<std::string>();
    for (std::list<std::string>::const_iterator spIter = from->begin();
         spIter != from->end();
         spIter++) {
      sections += "'";
      sections += (*spIter);
      sections += "' ";
      mySectionsToParse->push_back(*spIter);
    }
    ArLog::log(ArLog::Verbose, "Will parse section(s) %s", sections.c_str());
  }
  else
  {
    ArLog::log(ArLog::Verbose, "Will parse all sections");
  }
}
