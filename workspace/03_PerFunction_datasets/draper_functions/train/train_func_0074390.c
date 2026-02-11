postCoreInitialization()
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << Q_FUNC_INFO;


    onCurrentUserChanged();
    pluginManager()->addObject(m_UserListener = new MainWindowUserListener(this));
    connect(user(), SIGNAL(userChanged()), this, SLOT(onCurrentUserChanged()), Qt::UniqueConnection);
    connect(user(), SIGNAL(userDataChanged(int)), this, SLOT(onUserDataChanged(int)), Qt::UniqueConnection);
    connect(user(), SIGNAL(reset()), this, SLOT(onCurrentUserChanged()), Qt::UniqueConnection);
    connect(patient(), SIGNAL(currentPatientChanged()), this, SLOT(onCurrentPatientChanged()), Qt::UniqueConnection);

    contextManager()->updateContext();
    actionManager()->retranslateMenusAndActions();

    theme()->finishSplashScreen(this);

    manageIModeEnabledState();
    connect(modeManager(), SIGNAL(currentModeChanged(Core::IMode*)), this, SLOT(onCurrentModeChanged(Core::IMode*)), Qt::UniqueConnection);
    modeManager()->activateMode(Core::Constants::MODE_PATIENT_SEARCH);

    raise();
    show();


    setFocus();
}
