writeDefaultSettings(Core::ISettings *s)
{
    LOG_FOR("HprimPreferencesWidget", tkTr(Trans::Constants::CREATING_DEFAULT_SETTINGS_FOR_1).arg("HprimPreferencesWidget"));
    if (!s)
        s = settings();

    s->setValue(Constants::S_ACTIVATION, Constants::OnlyForFrance);
    s->setValue(Constants::S_DEFAULT_FILE_ENCODING, Constants::AutoDetect);
    QString defaultPath = QString("%1/%2")
            .arg(settings()->path(Core::ISettings::UserDocumentsPath))
            .arg("Hprim/");
    s->setValue(Constants::S_PATH_TO_SCAN, defaultPath);
    s->setValue(Constants::S_FILE_MANAGEMENT, Constants::StoreFileInPath);
    QString defaultStoringPath = QString("%1/%2")
            .arg(settings()->path(Core::ISettings::UserDocumentsPath))
            .arg("Hprim/Processed");
    Utils::checkDir(defaultStoringPath, true, "HprimPreferencesWidget");
    s->setValue(Constants::S_FILE_MANAGEMENT_STORING_PATH, defaultStoringPath);
}
