processName()

{ std::string::size_type shriekPos = name_.find('!') ;
  lengthName_ = name_.length() ;
  if (shriekPos == std::string::npos)
  { lengthMatch_ = lengthName_ ; }
  else
  { lengthMatch_ = shriekPos ;
    name_ = name_.substr(0,shriekPos)+name_.substr(shriekPos+1) ;
    lengthName_-- ; }

  return ; }
