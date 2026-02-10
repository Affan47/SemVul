GetAuthProfile(std::string name)
{
  std::stringstream query;
  query << "SELECT eperson, apikey, app_name, url FROM auth_profile WHERE "
    "profile_name='" << name << "'";

  midasAuthProfile profile;

  this->Database->ExecuteQuery(query.str().c_str());
  if(this->Database->GetNextRow())
    {
    profile.Name = name;
    profile.User = this->Database->GetValueAsString(0);
    profile.ApiKey = this->Database->GetValueAsString(1);
    profile.AppName = this->Database->GetValueAsString(2);
    profile.Url = this->Database->GetValueAsString(3);
    while(this->Database->GetNextRow());
    }
  return profile;
}
