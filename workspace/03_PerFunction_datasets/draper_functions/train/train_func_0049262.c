GetControl() const
{

    if (m_pControl2)
    {


        if ( m_pControl2->GetLastFocusTime() > m_pControl->GetLastFocusTime() )
            return m_pControl2;
    }
    return m_pControl;
}
