OnSetFocus( wxFocusEvent &WXUNUSED(event) )
{
    if ( GetParent() )
    {
        wxFocusEvent event( wxEVT_SET_FOCUS, GetParent()->GetId() );
        event.SetEventObject( GetParent() );
        if ( GetParent()->GetEventHandler()->ProcessEvent( event) )
            return;
    }


    if ( !m_hasFocus )
    {
        m_hasFocus = true;

        RefreshSelected();
    }
}
