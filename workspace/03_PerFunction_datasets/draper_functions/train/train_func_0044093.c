SplitBranch(nSearchTreeNode n,size_t depth)
{
    if (!n || !m_Nodes[n] || m_Nodes[n]->GetDepth()==depth)
        return n;


    SearchTreeNode* child = m_Nodes[n];

    nSearchTreeNode old_parent = child->GetParent();


    size_t parent_offset = depth - child->GetLabelStartDepth();
    nSearchTreeLabel labelno = child->GetLabelNo();

    unsigned int oldlabelstart = child->GetLabelStart();
    unsigned int oldlabellen = child->GetLabelLen();

    unsigned int middle_start = oldlabelstart;
    unsigned int middle_len = parent_offset;

    unsigned int child_start = middle_start + middle_len;
    unsigned int child_len = oldlabellen - middle_len;

    wxChar middle_char = m_Labels[labelno][middle_start];
    wxChar child_char = m_Labels[labelno][child_start];


    SearchTreeNode* newnode = CreateNode(depth,old_parent,labelno,middle_start,middle_len);
    m_Nodes.push_back(newnode);
    nSearchTreeNode middle = m_Nodes.size() - 1;


    child->SetParent(middle);
    child->SetLabel(labelno,child_start,child_len);
    child->RecalcDepth(this);
    newnode->m_Children[child_char]=n;
    child->UpdateItems(this);


    m_Nodes[old_parent]->m_Children[middle_char]=middle;

    return middle;
}
