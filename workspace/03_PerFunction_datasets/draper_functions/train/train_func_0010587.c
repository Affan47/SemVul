CheckTranslationPath(kwsys_stl::string & path)
{


  if(path.size() < 2)
    {
    return;
    }


  path += "/";


  kwsys_stl::map<kwsys_stl::string,kwsys_stl::string>::const_iterator it;
  for(it  = SystemTools::TranslationMap->begin();
      it != SystemTools::TranslationMap->end();
      ++it )
    {

    if(path.find( it->first ) == 0)
      {
      path = path.replace( 0, it->first.size(), it->second);
      }
    }


  path.erase(path.end()-1, path.end());
}
