WriteMakeRule(std::ostream& os,
                const char* comment,
                const char* target,
                const std::vector<std::string>& depends,
                const std::vector<std::string>& commands,
                bool symbolic,
                bool in_help)
{

  if(!target || !*target)
    {
    cmSystemTools::Error("No target for WriteMakeRule! called with comment: ",
                         comment);
    return;
    }

  std::string replace;


  if(comment)
    {
    replace = comment;
    std::string::size_type lpos = 0;
    std::string::size_type rpos;
    while((rpos = replace.find('\n', lpos)) != std::string::npos)
      {
      os << "# " << replace.substr(lpos, rpos-lpos) << "\n";
      lpos = rpos+1;
      }
    os << "# " << replace.substr(lpos) << "\n";
    }


  replace = target;
  std::string tgt = this->Convert(replace.c_str(),HOME_OUTPUT,MAKEFILE);
  const char* space = "";
  if(tgt.size() == 1)
    {


    space = " ";
    }


  if(symbolic)
    {
    if(const char* sym =
       this->Makefile->GetDefinition("CMAKE_MAKE_SYMBOLIC_RULE"))
      {
      os << cmMakeSafe(tgt) << space << ": " << sym << "\n";
      }
    }


  if(depends.empty())
    {

    os << cmMakeSafe(tgt) << space << ":\n";
    }
  else
    {


    for(std::vector<std::string>::const_iterator dep = depends.begin();
        dep != depends.end(); ++dep)
      {
      replace = *dep;
      replace = this->Convert(replace.c_str(),HOME_OUTPUT,MAKEFILE);
      os << cmMakeSafe(tgt) << space << ": " << cmMakeSafe(replace) << "\n";
      }
    }


  for(std::vector<std::string>::const_iterator i = commands.begin();
      i != commands.end(); ++i)
    {
    replace = *i;
    os << "\t" << replace.c_str() << "\n";
    }
  if(symbolic && !this->WatcomWMake)
    {
    os << ".PHONY : " << cmMakeSafe(tgt) << "\n";
    }
  os << "\n";

  if(in_help)
    {
    this->LocalHelp.push_back(target);
    }
}
