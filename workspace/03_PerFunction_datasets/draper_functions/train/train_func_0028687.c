GetAdjustedVerticalSashPosition(int pos) const
{
    int width = GetClientSize().GetWidth();

    if (width < m_minSize.x)
        pos = width/2;
    else if (pos <= m_minSize.x)
        pos = m_minSize.x;
    else if (pos >= width - m_minSize.x)
        pos = width - m_minSize.x;

    return pos;
}
