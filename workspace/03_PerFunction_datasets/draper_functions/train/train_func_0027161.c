stop()
{
    if (!plugin)
        return IPlugin::SynchronousShutdown;
    state = PluginSpec::Stopped;
    return plugin->aboutToShutdown();
}
