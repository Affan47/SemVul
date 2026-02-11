UpdateItems(BasicSearchTree* tree)
{
    SearchTreeNode* parentnode = tree->GetNode(m_Parent,true);
    if (!parentnode)
       return;
    SearchTreeItemsMap newmap;
    size_t mindepth = parentnode->GetDepth();
    SearchTreeItemsMap::const_iterator i;
    newmap.clear();


    for (i = m_Items.begin();i!=m_Items.end();i++)
    {
        if (i->first <= mindepth)
            parentnode->m_Items[i->first]=i->second;
        else
            newmap[i->first]=i->second;
    }
    m_Items.clear();
    for (i = newmap.begin();i!=newmap.end();i++)
        m_Items[i->first]=i->second;
}
