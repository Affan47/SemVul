contentHeightForWidth(int width) const
{
    if (m_netWidth > 0 && m_netHeight > 0)
        return (m_netHeight * width) / m_netWidth;
    if (!m_photo || m_photo->width() < 1)
        return -1;
    return (m_photo->height() * width) / m_photo->width();
}
