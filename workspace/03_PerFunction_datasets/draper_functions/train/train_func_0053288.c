CreateSingleModule(const char* fname,
                                         const char* moduleName,
                                         cmDocumentationSection &moduleSection)
{
  std::ifstream fin(fname);
  if(!fin)
    {
    std::cerr << "Internal error: can not open module." << fname << std::endl;
    return false;
    }
  std::string line;
  std::string text;
  std::string brief;
  brief = " ";
  bool newParagraph = true;
  while ( fin && cmSystemTools::GetLineFromStream(fin, line) )
    {
    if(line.size() && line[0] == '#')
      {

      if(line.size() <= 2)
        {
        text += "\n";
        newParagraph = true;
        }
      else if(line[2] == '-')
        {
        brief = line.c_str()+4;
        }
      else
        {

        if(line[1] == ' ' && line[2] == ' ')
          {
          if(!newParagraph)
            {
            text += "\n";
            newParagraph = true;
            }

          text += line.c_str()+1;
          text += "\n";
          }
        else if(line[1] == ' ')
          {
          if(!newParagraph)
            {
            text += " ";
            }
          newParagraph = false;

          text += line.c_str()+2;
          }
        else
          {
          if(!newParagraph)
            {
            text += " ";
            }
          newParagraph = false;

          text += line.c_str()+1;
          }
        }
      }
    else
      {
      if(text.length() < 2 && brief.length() == 1)
        {
        return false;
        }
      char* pname = strcpy(new char[strlen(moduleName)+1], moduleName);
      char* ptext = strcpy(new char[text.length()+1], text.c_str());
      this->ModuleStrings.push_back(pname);
      this->ModuleStrings.push_back(ptext);
      char* pbrief = strcpy(new char[brief.length()+1], brief.c_str());
      this->ModuleStrings.push_back(pbrief);
      moduleSection.Append(pname, pbrief, ptext);
      return true;
      }
    }
  return true;
}
