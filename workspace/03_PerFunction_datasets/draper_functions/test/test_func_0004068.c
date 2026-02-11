httpShouldTrace(HttpConn *conn, int dir, int item, cchar *ext)
{
    HttpTrace   *trace;

    mprAssert(0 <= dir && dir < HTTP_TRACE_MAX_DIR);
    mprAssert(0 <= item && item < HTTP_TRACE_MAX_ITEM);

    trace = &conn->trace[dir];
    if (trace->disable || trace->levels[item] > MPR->logLevel) {
        return -1;
    }
    if (ext) {
        if (trace->include && !mprLookupKey(trace->include, ext)) {
            trace->disable = 1;
            return -1;
        }
        if (trace->exclude && mprLookupKey(trace->exclude, ext)) {
            trace->disable = 1;
            return -1;
        }
    }
    return trace->levels[item];
}
