createValidateMenu(const QString &prescribeOnly,
                            const QString &savePrescribe,
                            const QString &saveOnly,
                            const QString &testOnly)
    {
        prescribe = new QAction(prescribeOnly, q->validateButton);
        prescribe->setIcon(theme()->icon(DrugsDB::Constants::I_PROTOCOL_PRESCRIBE, Core::ITheme::MediumIcon));
        prescribe->setIconVisibleInMenu(true);
        q->connect(prescribe, SIGNAL(triggered()), q, SLOT(prescribeRequested()));

        prescribeAndSave = new QAction(savePrescribe, q->validateButton);
        prescribeAndSave->setIcon(theme()->icon(DrugsDB::Constants::I_PROTOCOL_PRESCRIBEANDSAVE, Core::ITheme::MediumIcon));
        prescribeAndSave->setIconVisibleInMenu(true);
        q->connect(prescribeAndSave, SIGNAL(triggered()), q, SLOT(saveAndPrescribeRequested()));

        save = new QAction(saveOnly, q->validateButton);
        save->setIcon(theme()->icon(DrugsDB::Constants::I_PROTOCOL_SAVE, Core::ITheme::MediumIcon));
        save->setIconVisibleInMenu(true);
        q->connect(save, SIGNAL(triggered()), q, SLOT(saveRequested()));

        test = new QAction(testOnly, q->validateButton);
        test->setIcon(theme()->icon(DrugsDB::Constants::I_PROTOCOL_TESTONLY, Core::ITheme::MediumIcon));
        test->setIconVisibleInMenu(true);
        q->connect(test, SIGNAL(triggered()), q, SLOT(addTestOnlyRequested()));

        q->validateButton->addAction(prescribeAndSave);
        q->validateButton->addAction(prescribe);
        q->validateButton->addAction(save);
        q->validateButton->addAction(test);

        q->cancelButton->setText(tkTr(Trans::Constants::CANCEL));
        q->cancelButton->setIcon(theme()->icon(Core::Constants::ICONEXIT, Core::ITheme::MediumIcon));
    }
