initialize(const QStringList &arguments, QString *errorString)
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << "MainWinPlugin::initialize";
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);


    Core::ICore::instance()->translators()->addNewTranslator("plugin_fdmainwindow");

    m_MainWindow->initialize(QStringList(),0);
    return true;
}
