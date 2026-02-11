setupActions()
{

    KAction* abort = actionCollection()->addAction( QLatin1String( "game_abort" ));
    abort->setText(i18n("End game"));
    connect(abort, SIGNAL(triggered()), m_main, SLOT(abort()));

    KAction* pause = KStandardGameAction::pause(m_main, SLOT(togglePause()), actionCollection());
    m_main->setPauseAction(pause);
    KStandardGameAction::highscores(this, SLOT(highscores()), actionCollection());
    KStandardGameAction::quit(this, SLOT(close()), actionCollection());

    KAction* action;
    action = new KToggleAction(i18n("&Play Sounds"), this);
    action->setChecked(KollisionConfig::enableSounds());
    actionCollection()->addAction( QLatin1String( "options_sounds" ), action);
    connect(action, SIGNAL(triggered(bool)), m_main, SLOT(enableSounds(bool)));

    setupGUI(Create | Save | Keys | StatusBar);
}
