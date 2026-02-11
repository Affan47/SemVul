extensionsInitialized()
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << "ScriptPlugin::extensionsInitialized";


    addAutoReleasedObject(new Core::PluginAboutPage(pluginSpec(), this));
    connect(Core::ICore::instance(), SIGNAL(coreOpened()), this, SLOT(postCoreInitialization()));
}
