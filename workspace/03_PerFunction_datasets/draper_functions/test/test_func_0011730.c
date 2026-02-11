GetAdjustedHorizontalSashPosition(int pos) const
{
    int height = GetClientSize().GetHeight();

    if (height < m_minSize.y)
        pos = height/2;
    else if (pos <= m_minSize.y)
        return m_minSize.y;
    else if (pos >= height - m_minSize.y)
        return height - m_minSize.y;

    return pos;
}
