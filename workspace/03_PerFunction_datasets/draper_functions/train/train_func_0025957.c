GetWidth() const
{
    wxCHECK_MSG( m_rect, 0, _T("can't be called in this mode") );

    return m_rect->width;
}
