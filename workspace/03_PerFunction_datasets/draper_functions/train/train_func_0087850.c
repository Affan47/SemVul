split_get_private(JSContext *cx, JSObject *obj)
{
    do {
        if (JS_GET_CLASS(cx, obj) == &split_global_class.base)
            return (ComplexObject *) JS_GetPrivate(cx, obj);
        obj = JS_GetParent(cx, obj);
    } while (obj);

    return NULL;
}
