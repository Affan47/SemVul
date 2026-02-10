createEngine(const QString& managerName, const QMap<QString, QString>& parameters)
{
    m_engine = 0;

    QString builtManagerName = managerName.isEmpty() ? QContactManager::availableManagers().value(0) : managerName;
    if (builtManagerName == QLatin1String("memory")) {
        m_engine = new QContactManagerEngineV2Wrapper(QContactMemoryEngine::createMemoryEngine(parameters));
#ifdef QT_SIMULATOR
    } else if (builtManagerName == QLatin1String("simulator")) {
        m_engine = new QContactManagerEngineV2Wrapper(QContactSimulatorEngine::createSimulatorEngine(parameters));
#endif
    } else {
        int implementationVersion = parameterValue(parameters, QTCONTACTS_IMPLEMENTATION_VERSION_NAME, -1);

        bool found = false;
        bool loadedDynamic = false;


        loadStaticFactories();


        QList<QContactManagerEngineFactory*> factories = m_engines.values(builtManagerName);
        m_error = QContactManager::NoError;

        while(!found) {
            foreach (QContactManagerEngineFactory* f, factories) {
                QList<int> versions = f->supportedImplementationVersions();
                if (implementationVersion == -1 ||
                        versions.isEmpty() ||
                        versions.contains(implementationVersion)) {
                    QContactManagerEngine* engine = f->engine(parameters, &m_error);

                    m_engine = qobject_cast<QContactManagerEngineV2*>(engine);
                    if (!m_engine && engine) {

                        m_engine = new QContactManagerEngineV2Wrapper(engine);
                    }
                    found = true;
                    break;
                }
            }


            if (loadedDynamic || found)
                break;


            loadFactories();
            factories = m_engines.values(builtManagerName);
            loadedDynamic = true;
        }


        if (m_engine && (implementationVersion != -1 && m_engine->managerVersion() != implementationVersion)) {
            m_error = QContactManager::VersionMismatchError;
            m_engine = 0;
        }

        if (!m_engine) {
            if (m_error == QContactManager::NoError)
                m_error = QContactManager::DoesNotExistError;
            m_engine = new QContactInvalidEngine();
        }
    }
}
