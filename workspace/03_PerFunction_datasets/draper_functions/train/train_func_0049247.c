HandleMouseRightClick( int WXUNUSED(x), unsigned int WXUNUSED(y),
                                            wxMouseEvent& event )
{
    if ( m_propHover )
    {

        wxPGProperty* p = m_propHover;
        AddToSelectionFromInputEvent(p, m_colHover, &event);


        SendEvent( wxEVT_PG_RIGHT_CLICK, p );

        return true;
    }
    return false;
}
