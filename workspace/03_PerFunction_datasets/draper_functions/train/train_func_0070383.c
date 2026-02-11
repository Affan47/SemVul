process_key_event (guint key_val,
                                    guint key_code,
                                    guint modifiers)
{
    CKeyEvent key = translate_key(key_val, key_code, modifiers);

    if ( !m_pv->getStatusAttrValue(CIBusWinHandler::STATUS_ID_CN) ) {

        if ( !m_hotkey_profile->isModeSwitchKey(key) ) {
            m_hotkey_profile->rememberLastKey(key);
            return FALSE;
        }
    } else if ( m_hotkey_profile->isModeSwitchKey(key) ) {
        m_pv->onKeyEvent(CKeyEvent(IM_VK_ENTER, 0, 0));
        m_pv->setStatusAttrValue(CIMIWinHandler::STATUS_ID_CN, false);
        return TRUE;
    }

    return m_pv->onKeyEvent(key);
}
