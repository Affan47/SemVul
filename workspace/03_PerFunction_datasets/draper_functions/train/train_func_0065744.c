pixmap_size() const
{
    if (m_wasBlocked) return Cache::blockedPixmap->size();
    if (m_hadError)   return Cache::brokenPixmap->size();
    if (i)            return i->size();
    return QSize();
}
