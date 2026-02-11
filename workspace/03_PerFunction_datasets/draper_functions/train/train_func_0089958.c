SerializeLabels()
{
    wxString result;
    result << _T(" <labels>\n");
    for (unsigned int i=0;i<m_Labels.size();i++)
    {
        result << _T("  <label id=\"") << SearchTreeNode::U2S(i) << _T("\" data=\"") << SerializeLabel(i) << _T("\" />\n");
    }
    result << _T(" </labels>\n");
    return result;
}
