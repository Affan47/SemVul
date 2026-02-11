NotifyCleanWorkspace()
{
    if (m_CommandQueue.GetCount() == 0)
    {
        CodeBlocksEvent evt(cbEVT_CLEAN_WORKSPACE_STARTED, 0, 0, 0, this);
        Manager::Get()->ProcessEvent(evt);
    }
    Manager::Yield();
}
