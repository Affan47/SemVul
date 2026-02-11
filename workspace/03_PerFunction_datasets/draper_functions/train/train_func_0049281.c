Update(const wxTreeItemId &ti)
{
    wxString chkpath=m_fe->GetFullPath(ti);
    m_path=wxString(m_fe->GetFullPath(ti).c_str());
    m_wildcard=wxString(m_fe->m_WildCards->GetValue().c_str());
    GetTreeState(ti);
    if(Create()==wxTHREAD_NO_ERROR)
    {
        SetPriority(20);
        Run();
    }
}
