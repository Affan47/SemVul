OnPluginLoadingComplete(cb_unused CodeBlocksEvent& event)
{
    RefreshUI();
    if (!m_activeDebugger)
    {
        m_useTargetsDefault = true;
        FindTargetsDebugger();
    }
}
