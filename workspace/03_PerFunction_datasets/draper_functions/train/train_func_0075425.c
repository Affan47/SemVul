AddSourceGroup(const std::vector<std::string>& name,
                                const char* regex)
{
  cmSourceGroup* sg = 0;
  std::vector<std::string> currentName;
  int i = 0;
  const int lastElement = static_cast<int>(name.size()-1);
  for(i=lastElement; i>=0; --i)
    {
    currentName.assign(name.begin(), name.begin()+i+1);
    sg = this->GetSourceGroup(currentName);
    if(sg != 0)
      {
      break;
      }
    }


  if(i==lastElement)
    {

    if ( regex )
      {


      sg->SetGroupRegex(regex);
      }
    return;
    }
  else if(i==-1)
    {


    this->SourceGroups.push_back(cmSourceGroup(name[0].c_str(), regex));
    sg = this->GetSourceGroup(currentName);
    i = 0;
    }


  const char* fullname = sg->GetFullName();
  cmGlobalGenerator* gg = this->LocalGenerator->GetGlobalGenerator();
  if(strlen(fullname))
    {
    std::string guidName = "SG_Filter_";
    guidName += fullname;
    gg->CreateGUID(guidName.c_str());
    }
  for(++i; i<=lastElement; ++i)
    {
    sg->AddChild(cmSourceGroup(name[i].c_str(), 0, sg->GetFullName()));
    sg = sg->lookupChild(name[i].c_str());
    fullname = sg->GetFullName();
    if(strlen(fullname))
      {
      std::string guidName = "SG_Filter_";
      guidName += fullname;
      gg->CreateGUID(guidName.c_str());
      }
    }

  sg->SetGroupRegex(regex);
}
