OnDeleteEnvVarClick(wxCommandEvent& WXUNUSED(event))
{
#if defined(TRACE_ENVVARS)
  Manager::Get()->GetLogManager()->DebugLog(F(_T("OnDeleteEnvVarClick")));
#endif

  wxCheckListBox* lstEnvVars = XRCCTRL(*this, "lstEnvVars", wxCheckListBox);
  if (!lstEnvVars)
    return;

  int sel = lstEnvVars->GetSelection();
  if (sel == -1)
    return;

  wxString key = lstEnvVars->GetStringSelection().BeforeFirst(_T('=')).Trim(true).Trim(false);
  if (key.IsEmpty())
    return;

  if (cbMessageBox(_("Are you sure you want to delete this variable?"),
                   _("Confirmation"),
                   wxYES_NO | wxICON_QUESTION) == wxID_YES)
  {
    nsEnvVars::EnvvarDiscard(key);
    lstEnvVars->Delete(sel);
  }
}
