js_InitXMLClasses(JSContext *cx, JSObject *obj)
{
    if (!js_InitNamespaceClass(cx, obj))
        return NULL;
    if (!js_InitQNameClass(cx, obj))
        return NULL;
    if (!js_InitAttributeNameClass(cx, obj))
        return NULL;
    if (!js_InitAnyNameClass(cx, obj))
        return NULL;
    return js_InitXMLClass(cx, obj);
}
