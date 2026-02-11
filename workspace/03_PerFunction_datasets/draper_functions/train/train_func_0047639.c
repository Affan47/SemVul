extensionsInitialized()
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << "MainWinPlugin::extensionsInitialized";

    m_MainWindow->extensionsInitialized();
}
