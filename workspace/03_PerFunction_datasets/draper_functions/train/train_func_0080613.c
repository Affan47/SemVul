SetupEventHandling( wxWindow* argWnd, int id )
{
    wxWindow* wnd = argWnd;

    if ( argWnd == m_wndEditor )
    {
        CONNECT_CHILD(wxEVT_MOTION,(wxMouseEventFunction),OnMouseMoveChild)
        CONNECT_CHILD(wxEVT_LEFT_UP,(wxMouseEventFunction),OnMouseUpChild)
        CONNECT_CHILD(wxEVT_LEFT_DOWN,(wxMouseEventFunction),OnMouseClickChild)
        CONNECT_CHILD(wxEVT_RIGHT_UP,(wxMouseEventFunction),OnMouseRightClickChild)
        CONNECT_CHILD(wxEVT_ENTER_WINDOW,(wxMouseEventFunction),OnMouseEntry)
        CONNECT_CHILD(wxEVT_LEAVE_WINDOW,(wxMouseEventFunction),OnMouseEntry)
    }
    else
    {
        CONNECT_CHILD(wxEVT_NAVIGATION_KEY,(wxNavigationKeyEventFunction),OnNavigationKey)
    }
    CONNECT_CHILD(wxEVT_KEY_DOWN,(wxCharEventFunction),OnChildKeyDown)
    CONNECT_CHILD(wxEVT_KEY_UP,(wxCharEventFunction),OnChildKeyUp)
    CONNECT_CHILD(wxEVT_KILL_FOCUS,(wxFocusEventFunction),OnFocusEvent)
}
