EnvvarVetoUI(const wxString& key, wxCheckListBox* lstEnvVars, int sel)
{
#if defined(TRACE_ENVVARS)
  Manager::Get()->GetLogManager()->DebugLog(F(_T("EnvvarVetoUI")));
#endif

  if (wxGetEnv(key, NULL))
  {
    wxString recursion;
    if (platform::windows) recursion = _T("PATH=%PATH%;C:\\NewPath");
    else                   recursion = _T("PATH=$PATH:/new_path");

    wxString warn_exist;
    warn_exist.Printf(_("Warning: Environment variable '%s' is already set.\n"
                        "Continue with updating it's value?\n"
                        "(Recursions like '%s' will be considered.)"),
                        key.wx_str(), recursion.wx_str());

    if (cbMessageBox(warn_exist, _("Confirmation"),
                     wxYES_NO | wxICON_QUESTION) == wxID_NO)
    {
      if (lstEnvVars && (sel>=0))
        lstEnvVars->Check(sel, false);
      return true;
    }
  }

  return false;
}
