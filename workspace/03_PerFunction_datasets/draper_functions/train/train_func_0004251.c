initialize(const QStringList &arguments, QString *errorString)
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << "IcdPlugin::initialize";
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);


    Core::ICore::instance()->translators()->addNewTranslator("plugin_icd");
    messageSplash(tr("Initializing ICD10 plugin..."));

    return true;
}
