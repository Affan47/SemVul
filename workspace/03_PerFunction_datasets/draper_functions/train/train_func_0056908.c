configureSettings()
{
    if ( KConfigDialog::showDialog("settings") )
    {
        return;
    }
    KConfigDialog *dialog = new KConfigDialog(this, "settings", Settings::self());
    dialog->addPage(new KGameThemeSelector(dialog, Settings::self()), i18n("Theme"), "games-config-theme");
	dialog->setFaceType(KConfigDialog::Plain);
    connect(dialog, SIGNAL(settingsChanged(QString)), mpGameView, SLOT(settingsChanged()));

    dialog->show();
}
