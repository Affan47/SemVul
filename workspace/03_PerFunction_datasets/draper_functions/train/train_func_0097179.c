OnTimer(cb_unused wxTimerEvent& e)
{
    switch(status)
    {
    case 0:
        status = 1;
        m_timer->Start(scroll_millis, false);
        break;
    case 1:
        top -= 2;
        Move(left, top);
        if(top <= hMin)
        {
            status = 2;
            m_timer->Start(m_delay, true);
        }
        break;
    case 2:
        status = 3;
        m_timer->Start(scroll_millis, false);
        break;
    case 3:
        top += ks;
        Move(left, top);
        if(top > displayGeometry.GetBottom())
        {
            Hide();
            Destroy();
        }
        break;
    default:
        break;
    };
}
