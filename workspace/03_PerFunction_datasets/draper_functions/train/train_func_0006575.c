OnToggleFullScreen(cb_unused wxCommandEvent& event)
{
    ShowFullScreen( !IsFullScreen(), wxFULLSCREEN_NOTOOLBAR
                    | wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION );


    if ( IsFullScreen() )
    {


        wxSize containerSize = GetClientSize();
        wxSize buttonSize = m_pCloseFullScreenBtn->GetSize();


        m_pCloseFullScreenBtn->Move( containerSize.GetWidth() - buttonSize.GetWidth(),
                    containerSize.GetHeight() - buttonSize.GetHeight() );

        m_pCloseFullScreenBtn->Show( true );
        m_pCloseFullScreenBtn->Raise();
    }
    else
        m_pCloseFullScreenBtn->Show( false );
}
