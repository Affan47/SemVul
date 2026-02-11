OnTimer( wxTimerEvent &event )
{
    m_timer->Stop();
    delete m_timer;
    m_timer = NULL;


    if (m_button_style & wxCUSTBUT_BUTTON)
    {
        m_down = 0;
    }
    else if (m_button_style & wxCUSTBUT_TOGGLE)
    {
        if (m_eventType == wxEVT_LEFT_UP)
            m_down = event.GetId()%2 ? 0 : 1;
        else
            m_down = event.GetId()%2 ? 1 : 0;
    }
    else if (m_button_style & wxCUSTBUT_BUT_DCLICK_TOG)
    {
        if (m_eventType == wxEVT_LEFT_DCLICK)
            m_down = event.GetId()%2 ? 0 : 1;
        else
            m_down = event.GetId()%2 ? 1 : 0;
    }
    else if (m_button_style & wxCUSTBUT_TOG_DCLICK_BUT)
    {
        if (m_eventType == wxEVT_LEFT_UP)
            m_down = event.GetId()%2 ? 0 : 1;
        else
            m_down = event.GetId()%2 ? 1 : 0;
    }

    Refresh(false);
    SendEvent();
}
