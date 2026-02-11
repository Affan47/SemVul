SetTimeoutValue(JSContext *cx, jsdouble t)
{

    if (!(t <= MAX_TIMEOUT_INTERVAL)) {
        JS_ReportError(cx, "Excessive timeout value");
        return JS_FALSE;
    }
    gTimeoutInterval = t;
    if (!ScheduleWatchdog(cx->runtime, t)) {
        JS_ReportError(cx, "Failed to create the watchdog");
        return JS_FALSE;
    }
    return JS_TRUE;
}
