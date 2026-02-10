createActions()
{

    m_stopAct = new KToggleAction(KIcon(":/images/stop.png"), i18n("&Break at Next Statement"), this );
    m_stopAct->setIconText(i18n("Break at Next"));
    actionCollection()->addAction( "stop", m_stopAct );
    m_stopAct->setEnabled(true);
    connect(m_stopAct, SIGNAL(triggered(bool)), this, SLOT(stopAtNext()));

    m_continueAct = new KAction(KIcon(":/images/continue.png"), i18n("Continue"), this );
    actionCollection()->addAction( "continue", m_continueAct );
    m_continueAct->setShortcut(Qt::Key_F9);
    m_continueAct->setEnabled(false);
    connect(m_continueAct, SIGNAL(triggered(bool)), this, SLOT(continueExecution()));


    m_stepOverAct = new KAction(KIcon(":/images/step-over.png"), i18n("Step Over"), this );
    actionCollection()->addAction( "stepOver", m_stepOverAct );
    m_stepOverAct->setShortcut(Qt::Key_F10);
    m_stepOverAct->setEnabled(false);
    connect(m_stepOverAct, SIGNAL(triggered(bool)), this, SLOT(stepOver()) );


    m_stepIntoAct = new KAction(KIcon(":/images/step-into.png"), i18n("Step Into"), this );
    actionCollection()->addAction( "stepInto", m_stepIntoAct );
    m_stepIntoAct->setShortcut(Qt::Key_F11);
    m_stepIntoAct->setEnabled(false);

    connect(m_stepIntoAct, SIGNAL(triggered(bool)), this, SLOT(stepInto()));

    m_stepOutAct = new KAction(KIcon(":/images/step-out.png"), i18n("Step Out"), this );
    actionCollection()->addAction( "stepOut", m_stepOutAct );
    m_stepOutAct->setShortcut(Qt::Key_F12);
    m_stepOutAct->setEnabled(false);
    connect(m_stepOutAct, SIGNAL(triggered(bool)), this, SLOT(stepOut()) );

    m_reindentAction = new KToggleAction(i18n("Reindent Sources"), this);
    actionCollection()->addAction( "reindent", m_reindentAction );
    m_reindentAction->setChecked( m_reindentSources );
    connect(m_reindentAction, SIGNAL(toggled(bool)), this, SLOT(settingsChanged()));

    m_catchExceptionsAction = new KToggleAction(i18n("Report Exceptions"), this);
    actionCollection()->addAction( "except", m_catchExceptionsAction );
    m_catchExceptionsAction->setChecked( m_catchExceptions );
    connect(m_catchExceptionsAction, SIGNAL(toggled(bool)), this, SLOT(settingsChanged()));
}
