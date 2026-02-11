js_ValidContextPointer(JSRuntime *rt, JSContext *cx)
{
    JSCList *cl;

    for (cl = rt->contextList.next; cl != &rt->contextList; cl = cl->next) {
        if (cl == &cx->link)
            return JS_TRUE;
    }
    JS_RUNTIME_METER(rt, deadContexts);
    return JS_FALSE;
}
