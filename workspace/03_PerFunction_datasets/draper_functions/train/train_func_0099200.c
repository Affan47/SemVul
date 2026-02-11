OnChar(wxKeyEvent& evt)
{


    bool ctrl = evt.ControlDown();
#ifdef __WXMAC__


    bool alt = false;
#else
    bool alt  = evt.AltDown();
#endif
    bool skip = ((ctrl || alt) && ! (ctrl && alt));

#if wxUSE_UNICODE


    if (m_lastKeyDownConsumed && evt.GetUnicodeKey() > 255)
        m_lastKeyDownConsumed = false;
#endif

    if (!m_lastKeyDownConsumed && !skip) {
#if wxUSE_UNICODE
        int key = evt.GetUnicodeKey();
        bool keyOk = true;


        if (key <= 127) {
            key = evt.GetKeyCode();
            keyOk = (key <= 127);
        }
        if (keyOk) {
            m_swx->DoAddChar(key);
            return;
        }
#else
        int key = evt.GetKeyCode();

        if ( (key <= WXK_START) || (key > WXK_COMMAND) ) {

            m_swx->DoAddChar(key);
            return;
        }
#endif
    }

    evt.Skip();
}
