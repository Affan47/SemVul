postCoreInitialization()
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << Q_FUNC_INFO;
    m_CurrentView->initialize();
}
