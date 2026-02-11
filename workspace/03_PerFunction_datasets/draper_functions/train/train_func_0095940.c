showPause ()
{
    hideItems();

    if (!m_gameScene->items().contains(m_dimmOverlay))
    {
        m_gameScene->addItem(m_dimmOverlay);
    }

    if (!m_gameScene->items().contains(m_pauseLabel))
    {
        m_gameScene->addItem(m_pauseLabel);
    }

    if (!m_gameScene->items().contains(m_continueAfterPauseLabel))
    {
        m_gameScene->addItem(m_continueAfterPauseLabel);
    }
}
