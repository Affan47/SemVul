postCoreInitialization()
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << Q_FUNC_INFO;


    d->_patientWidgetManager->postCoreInitialization();
}
