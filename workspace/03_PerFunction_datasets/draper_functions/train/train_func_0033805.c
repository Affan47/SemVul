SupportsFeature(cbDebuggerFeature::Flags flag)
{
    DebuggerConfiguration &config = GetActiveConfigEx();

    if (config.IsGDB())
    {
        switch (flag)
        {
        case cbDebuggerFeature::Breakpoints:
        case cbDebuggerFeature::Callstack:
        case cbDebuggerFeature::CPURegisters:
        case cbDebuggerFeature::Disassembly:
        case cbDebuggerFeature::Watches:
        case cbDebuggerFeature::ValueTooltips:
        case cbDebuggerFeature::ExamineMemory:
        case cbDebuggerFeature::Threads:
        case cbDebuggerFeature::RunToCursor:
        case cbDebuggerFeature::SetNextStatement:
            return true;
        default:
            return false;
        }
    }
    else
    {
        switch (flag)
        {
        case cbDebuggerFeature::Breakpoints:
        case cbDebuggerFeature::Callstack:
        case cbDebuggerFeature::CPURegisters:
        case cbDebuggerFeature::Disassembly:
        case cbDebuggerFeature::Watches:
        case cbDebuggerFeature::ValueTooltips:
            return true;
        case cbDebuggerFeature::ExamineMemory:
        case cbDebuggerFeature::Threads:
        case cbDebuggerFeature::RunToCursor:
        case cbDebuggerFeature::SetNextStatement:
        default:
            return false;
        }
    }

    return false;
}
