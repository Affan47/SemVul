GetFullPath(const wxTreeItemId &ti)
{
    if(!ti.IsOk())
        return wxEmptyString;
    wxFileName path(m_root);
    if(ti!=m_Tree->GetRootItem())
    {
        std::vector<wxTreeItemId> vti;
        vti.push_back(ti);
        wxTreeItemId pti=m_Tree->GetItemParent(vti[0]);
        if(!pti.IsOk())
            return wxEmptyString;
        while(pti!=m_Tree->GetRootItem())
        {
            vti.insert(vti.begin(),pti);
            pti=m_Tree->GetItemParent(pti);
        }
        for(size_t i=0;i<vti.size();i++)
            path.Assign(path.GetFullPath(),m_Tree->GetItemText(vti[i]));
    }
    return path.GetFullPath();
}
