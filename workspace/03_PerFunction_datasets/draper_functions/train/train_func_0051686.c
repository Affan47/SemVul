prevLevel()
{

    if (m_timer->isActive())
        m_timer->stop();

    if (isPrevLevelAvailable())
    {
        switchToLevel(m_level-1);
    }
}
