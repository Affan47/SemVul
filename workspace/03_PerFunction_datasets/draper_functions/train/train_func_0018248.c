OnShowLogManager(cb_unused CodeBlocksLogEvent& event)
{
    if (!Manager::Get()->GetConfigManager(_T("message_manager"))->ReadBool(_T("/auto_hide"), false))
        return;

    m_LayoutManager.GetPane(m_pInfoPane).Show(true);
    DoUpdateLayout();
}
