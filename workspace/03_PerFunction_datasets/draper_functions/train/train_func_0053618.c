xml_getProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
{
    if (id == JS_DEFAULT_XML_NAMESPACE_ID) {
        *vp = JSVAL_VOID;
        return JS_TRUE;
    }

    return GetProperty(cx, obj, ID_TO_VALUE(id), vp);
}
