setGameType(int id)
{


    if ( m_dealer && m_dealer_map.value( id ) == m_dealer_map.value( m_dealer->gameId() ) )
    {
        m_dealer->recordGameStatistics();
        m_dealer->mapOldId( id );
        return;
    }


    if ( m_dealer )
    {
        m_dealer->recordGameStatistics();
        delete m_dealer;
        m_view->setScene(0);
        m_dealer = 0;
    }

    if ( !m_cardDeck )
    {
        KCardTheme theme = KCardTheme( Settings::cardTheme() );
        if ( !theme.isValid() )
            theme = KCardTheme( Settings::defaultCardThemeValue() );

        m_cardDeck = new KCardDeck( theme, this );
    }

    const DealerInfo * di = m_dealer_map.value(id, DealerInfoList::self()->games().first());
    m_dealer = di->createGame();
    m_dealer->setDeck( m_cardDeck );
    m_dealer->initialize();
    m_dealer->mapOldId( id );
    m_dealer->setSolverEnabled( m_solverEnabledAction->isChecked() );
    m_dealer->setAutoDropEnabled( m_autoDropEnabledAction->isChecked() );

    m_view->setScene( m_dealer );

    m_gameHelpAction->setText(i18nc("Is disabled and changes to \"Help &with Current Game\" when"
                                  " there is no current game.",
                                  "Help &with %1", di->baseName().replace('&', "&&")));

    connect(m_dealer, SIGNAL(solverStateChanged(QString)), SLOT(updateSolverDescription(QString)));
    connect(m_dealer, SIGNAL(updateMoves(int)), SLOT(slotUpdateMoves(int)));

    m_solverStatusLabel->setText(QString());
    m_solverStatusLabel->setVisible(true);
    m_moveCountStatusLabel->setText(QString());
    m_moveCountStatusLabel->setVisible(true);

    updateActions();
    updateSoundEngine();
}
