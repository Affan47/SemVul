OnAddScript(cb_unused wxCommandEvent& event)
{
    wxListBox* ctrl = XRCCTRL(*this, "lstPreScripts", wxListBox);
    if (!ctrl)
        return;

    wxFileName fname;
    if (ctrl->GetSelection())
        fname.Assign(ctrl->GetStringSelection());
    else if (ctrl->GetCount())
        fname.Assign(ctrl->GetString(ctrl->GetCount() - 1));
    fname.Normalize(wxPATH_NORM_ALL & ~wxPATH_NORM_CASE, m_Project->GetBasePath());

    EditPathDlg dlg(this,
                    fname.GetFullName(),
                    wxEmptyString,
                    _("Add script(s)"),
                    _("Select script file(s)"),
                    false,
                    true,
                    _("Script files (*.script)|*.script"));

    PlaceWindow(&dlg);
    if (dlg.ShowModal() != wxID_OK)
        return;

    wxArrayString paths = GetArrayFromString(dlg.GetPath());
    for (size_t i = 0; i < paths.GetCount(); ++i)
    {
        fname.Assign(paths[i]);
        fname.MakeRelativeTo(m_Project->GetBasePath());
        ctrl->Append(fname.GetFullPath());
        ctrl->SetSelection(ctrl->GetCount()-1);

        wxTreeCtrl* tc = XRCCTRL(*this, "tcOverview", wxTreeCtrl);
        wxTreeItemId sel = tc->GetSelection();
        CompileOptionsBase* base = sel == tc->GetRootItem()
                                    ? static_cast<CompileOptionsBase*>(m_Project)
                                    : static_cast<CompileOptionsBase*>(m_Project->GetBuildTarget(tc->GetItemText(sel)));
        base->AddBuildScript(fname.GetFullPath());
    }
}
