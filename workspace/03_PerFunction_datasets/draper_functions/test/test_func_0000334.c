OnUpdateCatchThrow(wxUpdateUIEvent &event)
{
    DebuggerConfiguration &config = GetActiveConfigEx();
    event.Enable(config.IsGDB() && IsStopped());
    event.Check(config.GetFlag(DebuggerConfiguration::CatchExceptions));
}
