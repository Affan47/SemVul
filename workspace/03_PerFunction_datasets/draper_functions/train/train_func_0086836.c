SetCTestConfigurationFromCMakeVariable(cmMakefile* mf,
  const char* dconfig, const char* cmake_var)
{
  const char* ctvar;
  ctvar = mf->GetDefinition(cmake_var);
  if ( !ctvar )
    {
    return false;
    }
  cmCTestLog(this, HANDLER_VERBOSE_OUTPUT,
             "SetCTestConfigurationFromCMakeVariable:"
             << dconfig << ":" << cmake_var << std::endl);
  this->SetCTestConfiguration(dconfig, ctvar);
  return true;
}
