RemoveBreakpoint(int idx, bool removeFromDriver)
{

    if (idx < 0 || idx >= (int)m_Breakpoints.size())
        return;

    BreakpointsList::iterator it = m_Breakpoints.begin();
    std::advance(it, idx);
    cb::shared_ptr<DebuggerBreakpoint> bp = *it;
    m_Breakpoints.erase(it);


    if (m_pDriver && removeFromDriver)
        m_pDriver->RemoveBreakpoint(bp);
}
