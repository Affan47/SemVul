js_TraceWatchPoints(JSTracer *trc, JSObject *obj)
{
    JSRuntime *rt;
    JSWatchPoint *wp;

    rt = trc->context->runtime;

    for (wp = (JSWatchPoint *)rt->watchPointList.next;
         &wp->links != &rt->watchPointList;
         wp = (JSWatchPoint *)wp->links.next) {
        if (wp->object == obj) {
            wp->sprop->trace(trc);
            if ((wp->sprop->attrs & JSPROP_SETTER) && wp->setter) {
                JS_CALL_OBJECT_TRACER(trc, js_CastAsObject(wp->setter),
                                      "wp->setter");
            }
            JS_SET_TRACING_NAME(trc, "wp->closure");
            js_CallValueTracerIfGCThing(trc, OBJECT_TO_JSVAL(wp->closure));
        }
    }
}
