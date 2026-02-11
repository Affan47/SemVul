JS_ClearWatchPoint(JSContext *cx, JSObject *obj, jsval id,
                   JSWatchPointHandler *handlerp, void **closurep)
{
    JSRuntime *rt;
    JSWatchPoint *wp;

    rt = cx->runtime;
    DBG_LOCK(rt);
    for (wp = (JSWatchPoint *)rt->watchPointList.next;
         &wp->links != &rt->watchPointList;
         wp = (JSWatchPoint *)wp->links.next) {
        if (wp->object == obj && SPROP_USERID(wp->sprop) == id) {
            if (handlerp)
                *handlerp = wp->handler;
            if (closurep)
                *closurep = wp->closure;
            return DropWatchPointAndUnlock(cx, wp, JSWP_LIVE);
        }
    }
    DBG_UNLOCK(rt);
    if (handlerp)
        *handlerp = NULL;
    if (closurep)
        *closurep = NULL;
    return JS_TRUE;
}
