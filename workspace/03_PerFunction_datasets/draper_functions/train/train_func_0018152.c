traceGcEventAtT_ (Capability *cap, StgWord64 ts, EventTypeNum tag)
{
#ifdef DEBUG
    if (RtsFlags.TraceFlags.tracing == TRACE_STDERR) {
        traceGcEvent_stderr(cap, tag);
    } else
#endif
    {

        postEventAtTimestamp(cap, ts, tag);
    }
}
