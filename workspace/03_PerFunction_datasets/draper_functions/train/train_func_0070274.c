GetExpandedNodes(wxTreeItemId ti, Expansion *exp)
{
    exp->name=m_Tree->GetItemText(ti);
    wxTreeItemIdValue cookie;
    wxTreeItemId ch=m_Tree->GetFirstChild(ti,cookie);
    while(ch.IsOk())
    {
        if(m_Tree->IsExpanded(ch))
        {
            Expansion *e=new Expansion();
            GetExpandedNodes(ch,e);
            exp->children.push_back(e);
        }
        ch=m_Tree->GetNextChild(ti,cookie);
    }
}
