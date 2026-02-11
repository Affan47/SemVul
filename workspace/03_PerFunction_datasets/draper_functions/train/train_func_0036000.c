GetXMLSettingFlags(JSContext *cx, uintN *flagsp)
{
    JSBool flag;


    if (!GetBooleanXMLSetting(cx, js_ignoreComments_str, &flag))
        return JS_FALSE;
    *flagsp = cx->xmlSettingFlags;
    return JS_TRUE;
}
