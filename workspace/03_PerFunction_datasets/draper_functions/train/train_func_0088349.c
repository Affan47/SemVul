AddAuthProfile(std::string user, std::string appName,
                                        std::string apiKey, std::string name,
                                        std::string url)
{
  this->DeleteProfile(name);

  std::stringstream query;
  query << "INSERT INTO auth_profile (profile_name, eperson, apikey, "
    "app_name, url) VALUES ('" << name << "', '" << user << "', '" << apiKey
    << "', '" << appName << "', '" << url << "')";

  return this->Database->ExecuteQuery(query.str().c_str());
}
