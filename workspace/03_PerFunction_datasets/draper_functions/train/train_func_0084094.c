configureSettings()
{
    if (KConfigDialog::showDialog(QLatin1String("settings")))
        return;
    KConfigDialog *dialog = new KConfigDialog(this, QLatin1String("settings"), Settings::self());
    dialog->addPage(new GeneralConfig(dialog), i18n("General"), QLatin1String("games-config-options"));
    dialog->addPage(new KgThemeSelector(m_view->getProvider()), i18n("Theme"), QLatin1String("games-config-theme"));
    dialog->addPage(new CustomGameConfig(dialog), i18n("Custom Game"), QLatin1String("games-config-custom"));
    connect(dialog, SIGNAL(settingsChanged(QString)), m_view, SLOT(setRotateDuration()));
    dialog->setHelp(QString(),QLatin1String("knetwalk"));
    dialog->show();
}
