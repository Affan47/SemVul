date_getUTCMilliseconds(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble result;

    if (!GetUTCTime(cx, JS_THIS_OBJECT(cx, vp), vp, &result))
        return JS_FALSE;

    if (JSDOUBLE_IS_FINITE(result))
        result = msFromTime(result);

    return js_NewNumberInRootedValue(cx, result, vp);
}
