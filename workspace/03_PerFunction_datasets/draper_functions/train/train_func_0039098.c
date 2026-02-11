OnBuildTargetChanged(cb_unused wxCommandEvent& event)
{
    DoTargetChange();
    CodeBlocksEvent e(cbEVT_PROJECT_TARGETS_MODIFIED);
    e.SetProject(m_Project);
    Manager::Get()->GetPluginManager()->NotifyPlugins(e);
}
