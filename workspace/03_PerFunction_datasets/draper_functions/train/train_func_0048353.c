OnMouseMove( wxMouseEvent &event )
{
    if ( !m_pTxtHelpCaption )
        return;

    int y = event.m_y;

    if ( m_dragStatus > 0 )
    {
        int sy = y - m_dragOffset;


        int bottom_limit = m_height - m_splitterHeight + 1;
        int top_limit = m_pPropGrid->m_lineHeight;
#if wxUSE_TOOLBAR
        if ( m_pToolbar ) top_limit += m_pToolbar->GetSize().y;
#endif

        if ( sy >= top_limit && sy < bottom_limit )
        {

            int change = sy - m_splitterY;
            if ( change )
            {
                m_splitterY = sy;

                m_pPropGrid->SetSize( m_width, m_splitterY - m_pPropGrid->GetPosition().y );
                UpdateDescriptionBox( m_splitterY, m_width, m_height );

                m_extraHeight -= change;
                InvalidateBestSize();
            }

        }

    }
    else
    {
        if ( y >= m_splitterY && y < (m_splitterY+m_splitterHeight+2) )
        {
            SetCursor ( m_cursorSizeNS );
            m_onSplitter = 1;
        }
        else
        {
            if ( m_onSplitter )
            {
                SetCursor ( wxNullCursor );
            }
            m_onSplitter = 0;
        }
    }
}
