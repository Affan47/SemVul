getObjName (unsigned maxLen) const
{ std::string name ;

  if (objName_.length() == 0)
  { name = dfltRowColName('o',0,maxLen) ; }
  else
  { name = objName_.substr(0,maxLen) ; }

  return (name) ; }
