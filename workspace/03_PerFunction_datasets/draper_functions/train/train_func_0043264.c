DoRecreateTargetMenu()
{
    if (!IsAttached())
        return;

    if (m_pToolTarget)
        m_pToolTarget->Freeze();
    wxMenuBar* mbar = Manager::Get()->GetAppFrame()->GetMenuBar();
    if (mbar)
        mbar->Freeze();

    do
    {

        DoClearTargetMenu();
        if (m_pToolTarget)
            m_pToolTarget->Clear();


        if (!CheckProject())
            break;


        if (!m_Targets.GetCount())
            break;

        wxString tgtStr(m_pProject->GetFirstValidBuildTargetName());


        if (cbWorkspace* wsp = Manager::Get()->GetProjectManager()->GetWorkspace())
        {
          const wxString preferredTarget = wsp->GetPreferredTarget();
          tgtStr = preferredTarget;
          if ( !IsValidTarget(tgtStr) )
              tgtStr = m_pProject->GetActiveBuildTarget();
          if ( !IsValidTarget(tgtStr) )
              tgtStr = m_pProject->GetFirstValidBuildTargetName();
          if ( preferredTarget.IsEmpty() )
              wsp->SetPreferredTarget(tgtStr);
        }


        for (size_t x = 0; x < m_Targets.GetCount(); ++x)
        {
            if (m_TargetMenu)
            {
                wxString help;
                help.Printf(_("Build target '%s' in current project"), GetTargetString(x).wx_str());
                m_TargetMenu->AppendCheckItem(idMenuSelectTargetOther[x], GetTargetString(x), help);
            }
            if (m_pToolTarget)
                m_pToolTarget->Append(GetTargetString(x));
        }


        Connect( idMenuSelectTargetOther[0],  idMenuSelectTargetOther[MAX_TARGETS - 1],
                wxEVT_COMMAND_MENU_SELECTED,
                (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                &CompilerGCC::OnSelectTarget );


        m_TargetIndex = m_Targets.Index(tgtStr);
        m_RealTargetIndex = m_TargetIndex - m_RealTargetsStartIndex;
        if (m_RealTargetIndex < 0)
            m_RealTargetIndex = -1;

        DoUpdateTargetMenu(m_TargetIndex);


        if (m_pToolTarget)
            m_pToolTarget->SetSelection(m_TargetIndex);


        SwitchCompiler(m_pProject->GetCompilerID());
    }
    while (false);

    if (mbar)
        mbar->Thaw();
    if (m_pToolTarget)
        m_pToolTarget->Thaw();
}
