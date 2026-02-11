xml_setAttributes(JSContext *cx, JSObject *obj, jsid id, JSProperty *prop,
                  uintN *attrsp)
{
    JSBool found;

    if (!FoundProperty(cx, obj, id, prop, &found))
        return JS_FALSE;
    if (found) {
        JS_ReportErrorNumber(cx, js_GetErrorMessage, NULL,
                             JSMSG_CANT_SET_XML_ATTRS);
    }
    return !found;
}
