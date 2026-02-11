OnCustomPaint( wxDC& dc,
                                         const wxRect& rect,
                                         wxPGPaintData& )
{
    if ( m_pBitmap || (m_pImage && m_pImage->Ok() ) )
    {


        if ( !m_pBitmap )
        {
            m_pImage->Rescale( rect.width, rect.height );
            m_pBitmap = new wxBitmap( *m_pImage );
            delete m_pImage;
            m_pImage = NULL;
        }

        dc.DrawBitmap( *m_pBitmap, rect.x, rect.y, false );
    }
    else
    {

        dc.SetBrush( *wxWHITE_BRUSH );
        dc.DrawRectangle ( rect );
    }
}
