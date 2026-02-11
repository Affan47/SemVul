DestroyControls(bool destr_control)
{
    if (Manager::Get()->IsAppShuttingDown())
        return;
    Manager::Get()->GetAppWindow()->RemoveEventHandler(this);
    if (destr_control)
    {
        m_pPanel->Destroy();
        m_pPanel = nullptr;
    }
}
