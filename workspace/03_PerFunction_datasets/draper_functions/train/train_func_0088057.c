ResetBreakpoint(cb::shared_ptr<DebuggerBreakpoint> bp)
{

    if (m_pDriver)
    {
        m_pDriver->RemoveBreakpoint(bp);
        m_pDriver->AddBreakpoint(bp);
    }
}
