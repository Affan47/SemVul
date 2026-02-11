CreateBitmap( const wxRect &rect )
{
    if (!m_owner)
        return;

    wxRect refreshRect(rect);
    wxRect clientRect(m_owner->GetPlotAreaRect());
    refreshRect.Intersect(clientRect);

    if ((refreshRect.width == 0) || (refreshRect.height == 0)) return;


    if (!m_bitmap.Ok() || (clientRect.width  != m_bitmap.GetWidth()) ||
                          (clientRect.height != m_bitmap.GetHeight()) )
    {
        m_bitmap.Create(clientRect.width, clientRect.height);
        refreshRect = clientRect;
    }

    wxMemoryDC mdc;
    mdc.SelectObject( m_bitmap );
    m_owner->DrawAreaWindow( &mdc, refreshRect );
    mdc.SelectObject( wxNullBitmap );
}
