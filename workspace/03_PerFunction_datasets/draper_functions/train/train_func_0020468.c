GetEnvironmentVariables()
{
  std::vector<std::string> env;
  int cc;
  for ( cc = 0; environ[cc]; ++ cc )
    {
    env.push_back(environ[cc]);
    }
  return env;
}
