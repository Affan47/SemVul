regexp_toString(JSContext *cx, uintN argc, jsval *vp)
{
    JSObject *obj;

    obj = JS_THIS_OBJECT(cx, vp);
    return obj && js_regexp_toString(cx, obj, vp);
}
