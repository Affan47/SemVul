DeleteProperty(WatchesProperty &prop)
{
    cb::shared_ptr<cbWatch> watch = prop.GetWatch();
    if (!watch)
        return;

    cbDebuggerPlugin *debugger = Manager::Get()->GetDebuggerManager()->GetDebuggerHavingWatch(watch);
    if (debugger)
        debugger->DeleteWatch(watch);

    wxPGProperty *parent = prop.GetParent();
    if (parent && parent->IsRoot())
    {
        for (WatchItems::iterator it = m_watches.begin(); it != m_watches.end(); ++it)
        {
            if (!it->property)
                continue;
            if (it->property == &prop)
            {
                m_watches.erase(it);
                break;
            }
        }
        prop.DeleteChildren();
        m_grid->DeleteProperty(&prop);
    }
}
