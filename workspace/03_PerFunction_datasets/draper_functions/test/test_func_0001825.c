setupStatusBar()
{
    m_gameTipLabel = new QLabel(i18n("Select a tile"), statusBar());
    statusBar()->addWidget(m_gameTipLabel, 1);

    m_gameTimerLabel = new QLabel(i18n("Time: 0:00:00"), statusBar());
    statusBar()->addWidget(m_gameTimerLabel);

    m_gameTilesLabel = new QLabel(i18n("Removed: 0/0"), statusBar());
    statusBar()->addWidget(m_gameTilesLabel);

    m_gameCheatLabel = new QLabel(i18n("Cheat mode"), statusBar());
    statusBar()->addWidget(m_gameCheatLabel);
    m_gameCheatLabel->hide();
}
