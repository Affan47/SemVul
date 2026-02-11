split_innerObject(JSContext *cx, JSObject *obj)
{
    ComplexObject *cpx;

    cpx = (ComplexObject *) JS_GetPrivate(cx, obj);
    if (cpx->frozen) {
        JS_ASSERT(!cpx->isInner);
        return obj;
    }
    return !cpx->isInner ? cpx->inner : obj;
}
