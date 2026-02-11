mapper()
{
    if ( m_inst )
        return m_inst;
    m_inst = new JSEventMapper();
    return m_inst;
}
