operator++()
{
    if( m_end )
        return *this;


    size_t count = m_AP->getPropertyCount();
    while( m_pocol.empty() )
    {
        if( m_apPropertyNumber == count )
        {
            m_end = true;
            return *this;
        }
        setup_pocol();
        ++m_apPropertyNumber;
    }

    std::string pred = m_pocoliter->first.toString();
    PD_Object   obj  = m_pocoliter->second;
    m_current = PD_RDFStatement( m_subject, pred, obj );
    ++m_pocoliter;
    if( m_pocoliter == m_pocol.end() )
    {
        m_pocol.clear();
    }

    return *this;
}
