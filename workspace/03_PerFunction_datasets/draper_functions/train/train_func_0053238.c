Initialize(wxString token)
{
    m_UnaryOperator = false;
    m_Token = token;
    m_Type = ParseNodeType(m_Token);
    m_Priority = GetNodeTypePriority(m_Type);
}
