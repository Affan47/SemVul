GetLineFromStream(istream& is,
  std::string& line, bool *has_newline = 0)
{
  const int bufferSize = 1024;
  char buffer[bufferSize];
  line = "";
  bool haveData = false;
  if ( has_newline )
    {
    *has_newline = false;
    }


  while((is.getline(buffer, bufferSize), is.gcount() > 0))
    {
    haveData = true;
    line.append(buffer);


    if(strlen(buffer) < static_cast<size_t>(is.gcount()))
      {
      if ( has_newline )
        {
        *has_newline = true;
        }
      break;
      }


    is.clear(is.rdstate() & ~ios::failbit);
    }
  return haveData;
}
