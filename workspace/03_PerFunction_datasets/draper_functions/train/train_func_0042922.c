WriteTargetRequiresRules()
{
  std::vector<std::string> depends;
  std::vector<std::string> no_commands;


  std::string depTarget =
    this->LocalGenerator->GetRelativeTargetDirectory(*this->Target);
  depTarget += "/requires";


  std::string relPath = this->LocalGenerator->GetHomeRelativeOutputPath();
  std::string objTarget;
  for(std::vector<std::string>::const_iterator obj = this->Objects.begin();
      obj != this->Objects.end(); ++obj)
    {
    objTarget = relPath;
    objTarget += *obj;
    objTarget += ".requires";
    depends.push_back(objTarget);
    }


  this->LocalGenerator->WriteMakeRule(*this->BuildFileStream, 0,
                                      depTarget.c_str(),
                                      depends, no_commands, true);
}
