initialize(const QStringList &arguments, QString *errorString)
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << "BaseWidgetsPlugin::initialize";

    Q_UNUSED(arguments);
    Q_UNUSED(errorString);
    m_Factory = new BaseWidgetsFactory(this);
    m_Factory->initialize(arguments,errorString);
    m_CalcFactory = new CalculationWidgetsFactory(this);
    m_CalcFactory->initialize(arguments,errorString);
    return true;
}
