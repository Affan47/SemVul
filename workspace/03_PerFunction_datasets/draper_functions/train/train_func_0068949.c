xml_defaultValue(JSContext *cx, JSObject *obj, JSType hint, jsval *vp)
{
    JSXML *xml;

    if (hint == JSTYPE_OBJECT) {

        xml = (JSXML *) obj->getPrivate();
        if (xml->xml_class != JSXML_CLASS_LIST) {
            obj = ToXMLList(cx, OBJECT_TO_JSVAL(obj));
            if (!obj)
                return JS_FALSE;
        }
        *vp = OBJECT_TO_JSVAL(obj);
        return JS_TRUE;
    }

    return JS_CallFunctionName(cx, obj, js_toString_str, 0, NULL, vp);
}
