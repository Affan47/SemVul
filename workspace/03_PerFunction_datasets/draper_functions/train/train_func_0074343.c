RefreshUI()
{
    m_menuHandler->SetActiveDebugger(m_activeDebugger);
    m_menuHandler->RebuildMenus();
    RefreshBreakpoints(m_activeDebugger);

    if (m_activeDebugger)
    {
        if (m_backtraceDialog)
            m_backtraceDialog->EnableWindow(m_activeDebugger->SupportsFeature(cbDebuggerFeature::Callstack));
        if (m_cpuRegistersDialog)
            m_cpuRegistersDialog->EnableWindow(m_activeDebugger->SupportsFeature(cbDebuggerFeature::CPURegisters));
        if (m_disassemblyDialog)
            m_disassemblyDialog->EnableWindow(m_activeDebugger->SupportsFeature(cbDebuggerFeature::Disassembly));
        if (m_examineMemoryDialog)
            m_examineMemoryDialog->EnableWindow(m_activeDebugger->SupportsFeature(cbDebuggerFeature::ExamineMemory));
        if (m_threadsDialog)
            m_threadsDialog->EnableWindow(m_activeDebugger->SupportsFeature(cbDebuggerFeature::Threads));
    }
    if (m_watchesDialog)
        m_watchesDialog->RefreshUI();
    if (m_breakPointsDialog)
        m_breakPointsDialog->Reload();
}
