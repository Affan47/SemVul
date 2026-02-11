initialize(const QStringList &arguments, QString *errorString)
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << "TemplatesPlugin::initialize";
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);

    return true;
}
