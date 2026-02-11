xml_settings(JSContext *cx, uintN argc, jsval *vp)
{
    JSObject *settings;
    JSObject *obj;

    settings = JS_NewObject(cx, NULL, NULL, NULL);
    if (!settings)
        return JS_FALSE;
    *vp = OBJECT_TO_JSVAL(settings);
    obj = JS_THIS_OBJECT(cx, vp);
    return obj && CopyXMLSettings(cx, obj, settings);
}
