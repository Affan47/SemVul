Combine(wxDouble i)
{
    if      (i < m_min) { m_min = i; return true; }
    else if (i > m_max) { m_max = i; return true; }
    return false;
}
