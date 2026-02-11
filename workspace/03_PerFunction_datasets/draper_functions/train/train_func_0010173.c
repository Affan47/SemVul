aboutToShutdown()
{
    if (Utils::Log::warnPluginsCreation())
        WARN_FUNC;


    if (m_prefPage) {
        removeObject(m_prefPage);
        delete m_prefPage;
        m_prefPage = 0;
    }


    DataPack::DataPackCore &core = DataPack::DataPackCore::instance(this);
#ifdef FREEMEDFORMS
    if (user()) {
        user()->setValue(Core::IUser::DataPackConfig, core.serverManager()->xmlConfiguration());
        user()->saveChanges();
    }
#endif

#ifdef FREEACCOUNT
    if (user()) {
        user()->setValue(Core::IUser::DataPackConfig, core.serverManager()->xmlConfiguration());
        user()->saveChanges();
    }
#endif

#ifdef FREEDIAMS
    QByteArray s = QByteArray(core.serverManager()->xmlConfiguration().toUtf8()).toBase64();
    settings()->setValue("datapack/server/config", s);
#endif

    return SynchronousShutdown;
}
