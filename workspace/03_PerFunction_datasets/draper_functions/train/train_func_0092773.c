GetEnvvarsBySetPath(const wxString& set_path)
{
#if defined(TRACE_ENVVARS)
  Manager::Get()->GetLogManager()->DebugLog(F(_T("GetEnvvarsBySetPath")));
#endif

  wxArrayString envvars;
  EV_DBGLOG(_T("EnvVars: Searching for envvars in path '%s'."), set_path.wx_str());

  ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("envvars"));
  if (!cfg || set_path.IsEmpty())
    return envvars;

  wxArrayString envvars_keys = cfg->EnumerateKeys(set_path);
  unsigned int  num_envvars  = envvars_keys.GetCount();
  for (unsigned int i=0; i<num_envvars; ++i)
  {
    wxString envvar = cfg->Read(set_path+_T("/")+envvars_keys[i]);
    if (!envvar.IsEmpty())
      envvars.Add(envvar);
    else
      EV_DBGLOG(_T("EnvVars: Warning: empty envvar detected and skipped."));
  }
  EV_DBGLOG(_T("EnvVars: Read %lu/%u envvars in path '%s'."),
    static_cast<unsigned long>(envvars.GetCount()), num_envvars, set_path.wx_str());

  return envvars;
}
