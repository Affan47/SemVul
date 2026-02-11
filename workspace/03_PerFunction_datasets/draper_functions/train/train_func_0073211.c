js_IsFunctionQName(JSContext *cx, JSObject *obj, jsid *funidp)
{
    if (OBJ_GET_CLASS(cx, obj) == &js_QNameClass.base)
        return IsFunctionQName(cx, obj, funidp);
    *funidp = 0;
    return JS_TRUE;
}
