KeyEventToActions(wxKeyEvent &event, int* pSecond) const
{


    int keycode = event.GetKeyCode();

#if wxCHECK_VERSION(2,8,0)
    int modifiers = event.GetModifiers();
#else
    int modifiers = wxPG_wxKeyEvent_GetModifiers(event);
#endif

    wxASSERT( !(modifiers&~(0xFFFF)) );

    int hashMapKey = (keycode & 0xFFFF) | ((modifiers & 0xFFFF) << 16);

    wxPGHashMapI2I::const_iterator it = m_actionTriggers.find(hashMapKey);

    if ( it == m_actionTriggers.end() )
        return 0;

    if ( pSecond )
    {
        int second = (it->second>>16) & 0xFFFF;
        *pSecond = second;
    }

    return (it->second & 0xFFFF);
}
