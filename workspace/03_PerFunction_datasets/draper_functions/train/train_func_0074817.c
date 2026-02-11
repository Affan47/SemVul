OnMenuUpdate(cb_unused wxCommandEvent &event)
{
    WatchesProperty *selected = static_cast<WatchesProperty*>(m_grid->GetSelection());
    if (!selected)
        return;
    cb::shared_ptr<cbWatch> watch = selected->GetWatch();
    if (!watch)
        return;
    watch = cbGetRootWatch(watch);
    cbDebuggerPlugin *plugin = Manager::Get()->GetDebuggerManager()->GetActiveDebugger();
    if (plugin)
        plugin->UpdateWatch(watch);
}
