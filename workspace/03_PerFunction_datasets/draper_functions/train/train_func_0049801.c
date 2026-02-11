UpdateChoices()
{
    if (m_CurrentSet.IsEmpty())
        m_CurrentSet = _T("default");

    wxArrayString sets = m_CfgMan->EnumerateSubPaths(cSets);
    wxArrayString vars = m_CfgMan->EnumerateSubPaths(cSets + m_CurrentSet + _T("/"));
    sets.Sort();
    vars.Sort();

    m_SelSet->Clear();
    m_SelSet->Append(sets);
    m_SelVar->Clear();
    m_SelVar->Append(vars);

    if (m_CurrentVar.IsEmpty() && m_SelVar->GetCount() > 0)
        m_CurrentVar = m_SelVar->GetString(0);

    m_SelSet->SetStringSelection(m_CurrentSet);
    m_SelVar->SetStringSelection(m_CurrentVar);
}
