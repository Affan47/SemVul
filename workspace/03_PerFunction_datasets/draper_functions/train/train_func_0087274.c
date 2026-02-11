CreateBitmap()
{
    if (!m_owner)
        return;

    m_owner->UpdateWindowSize();
    wxSize clientSize = GetClientSize();
    if ((clientSize.x < 2) || (clientSize.y < 2)) return;

    if (!m_bitmap.Ok() || (clientSize.x != m_bitmap.GetWidth()) ||
                          (clientSize.y != m_bitmap.GetHeight()) )
    {
        m_bitmap.Create(clientSize.x, clientSize.y);
    }

    wxMemoryDC mdc;
    mdc.SelectObject( m_bitmap );
    if (IsXAxis())
        m_owner->DrawXAxis( &mdc, true );
    else
        m_owner->DrawYAxis( &mdc, true );

    mdc.SelectObject( wxNullBitmap );
}
