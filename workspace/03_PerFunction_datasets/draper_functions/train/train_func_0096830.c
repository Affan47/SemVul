OnScriptMoveDown(cb_unused wxSpinEvent& event)
{
    wxListBox* ctrl = XRCCTRL(*this, "lstPreScripts", wxListBox);
    if (!ctrl || ctrl->GetSelection() == (int)(ctrl->GetCount()) - 1)
        return;

    wxTreeCtrl* tc = XRCCTRL(*this, "tcOverview", wxTreeCtrl);
    wxTreeItemId sel = tc->GetSelection();
    CompileOptionsBase* base = sel == tc->GetRootItem()
                                ? static_cast<CompileOptionsBase*>(m_Project)
                                : static_cast<CompileOptionsBase*>(m_Project->GetBuildTarget(tc->GetItemText(sel)));

    int isel = ctrl->GetSelection();
    wxString ssel = ctrl->GetStringSelection();
    wxArrayString scripts = base->GetBuildScripts();
    scripts.RemoveAt(isel);
    ctrl->Delete(isel);
    ++isel;
    ctrl->Insert(ssel, isel);
    scripts.Insert(ssel, isel);
    ctrl->SetSelection(isel);
    base->SetBuildScripts(scripts);
}
