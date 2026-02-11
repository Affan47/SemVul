namespace_toString(JSContext *cx, uintN argc, jsval *vp)
{
    JSObject *obj;

    obj = JS_THIS_OBJECT(cx, vp);
    if (!JS_InstanceOf(cx, obj, &js_NamespaceClass.base, vp))
        return JS_FALSE;
    *vp = obj->fslots[JSSLOT_URI];
    return JS_TRUE;
}
