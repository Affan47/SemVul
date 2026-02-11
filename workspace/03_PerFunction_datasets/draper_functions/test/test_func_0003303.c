GetCTestConfiguration(const char *name)
{
  if ( this->CTestConfigurationOverwrites.find(name) !=
    this->CTestConfigurationOverwrites.end() )
    {
    return this->CTestConfigurationOverwrites[name];
    }
  return this->CTestConfiguration[name];
}
