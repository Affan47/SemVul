markOutputsChanged(Plugin *plugin)
{
    OutputMap::iterator i = m_pluginOutputs.find(plugin);


    if (i != m_pluginOutputs.end()) {

        Plugin::OutputList *list = i->second;
        m_pluginOutputs.erase(i);
        delete list;
    }
}
