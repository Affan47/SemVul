js_HasOwnPropertyHelper(JSContext *cx, JSLookupPropOp lookup, uintN argc,
                        jsval *vp)
{
    jsid id;
    JSObject *obj;

    if (!JS_ValueToId(cx, argc != 0 ? vp[2] : JSVAL_VOID, &id))
        return JS_FALSE;
    obj = JS_THIS_OBJECT(cx, vp);
    return obj && js_HasOwnProperty(cx, lookup, obj, id, vp);
}
