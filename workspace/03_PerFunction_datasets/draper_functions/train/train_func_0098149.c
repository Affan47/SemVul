GetActiveConfig()
{
    DebuggerManager::RegisteredPlugins &allPlugins = Manager::Get()->GetDebuggerManager()->GetAllDebuggers();

    DebuggerManager::RegisteredPlugins::iterator it = allPlugins.find(this);
    if (it == allPlugins.end())
        cbAssert(false);
    cbDebuggerConfiguration *config = it->second.GetConfiguration(m_ActiveConfig);
    if (!config)
        return *it->second.GetConfigurations().front();
    else
        return *config;
}
