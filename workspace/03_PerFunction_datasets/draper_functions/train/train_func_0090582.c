SetRange( double min_val, double max_val )
{

    m_min = min_val;
    m_max = max_val;

    if (HasRange())
    {
        if (m_value > m_max)
            SetValue(m_max);
        else if (m_value < m_min)
            SetValue(m_min);
    }
}
