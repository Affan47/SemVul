js_GetPropertyByIdWithFakeFrame(JSContext *cx, JSObject *obj, JSObject *scopeobj, jsid id,
                                jsval *vp)
{
    FakeFrame frame(cx, scopeobj);
    return JS_GetPropertyById(cx, obj, id, vp);
}
