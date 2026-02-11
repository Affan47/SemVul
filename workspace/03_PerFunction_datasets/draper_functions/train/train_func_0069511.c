contentHeightForWidth(int width) const
{
    if (m_pixmap.width() < 1)
        return -1;
    return (m_pixmap.height() * width) / m_pixmap.width();
}
