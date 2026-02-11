date_getTimezoneOffset(JSContext *cx, uintN argc, jsval *vp)
{
    JSObject *obj;
    jsdouble utctime, localtime, result;

    obj = JS_THIS_OBJECT(cx, vp);
    if (!GetUTCTime(cx, obj, vp, &utctime))
        return JS_FALSE;
    if (!GetAndCacheLocalTime(cx, obj, NULL, &localtime))
        return JS_FALSE;


    result = (utctime - localtime) / msPerMinute;
    return js_NewNumberInRootedValue(cx, result, vp);
}
