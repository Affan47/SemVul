xml_processingInstructions_helper(JSContext *cx, JSObject *obj, JSXML *xml,
                                  JSObject *nameqn, jsval *vp)
{
    JSXML *list, *vxml;
    JSBool ok;
    JSObject *kidobj;
    jsval v;
    uint32 i, n;
    JSString *localName;

    list = xml_list_helper(cx, xml, vp);
    if (!list)
        return JS_FALSE;

    list->xml_targetprop = nameqn;
    ok = JS_TRUE;

    if (xml->xml_class == JSXML_CLASS_LIST) {

        JSXMLArrayCursor cursor(&xml->xml_kids);
        while (JSXML *kid = (JSXML *) cursor.getNext()) {
            if (kid->xml_class == JSXML_CLASS_ELEMENT) {
                ok = js_EnterLocalRootScope(cx);
                if (!ok)
                    break;
                kidobj = js_GetXMLObject(cx, kid);
                if (kidobj) {
                    ok = xml_processingInstructions_helper(cx, kidobj, kid,
                                                           nameqn, &v);
                } else {
                    ok = JS_FALSE;
                    v = JSVAL_NULL;
                }
                js_LeaveLocalRootScopeWithResult(cx, v);
                if (!ok)
                    break;
                vxml = (JSXML *) JSVAL_TO_OBJECT(v)->getPrivate();
                if (JSXML_LENGTH(vxml) != 0) {
                    ok = Append(cx, list, vxml);
                    if (!ok)
                        break;
                }
            }
        }
    } else {

        for (i = 0, n = JSXML_LENGTH(xml); i < n; i++) {
            JSXML *kid = XMLARRAY_MEMBER(&xml->xml_kids, i, JSXML);
            if (kid && kid->xml_class == JSXML_CLASS_PROCESSING_INSTRUCTION) {
                localName = GetLocalName(nameqn);
                if (IS_STAR(localName) ||
                    js_EqualStrings(localName, GetLocalName(kid->name))) {
                    ok = Append(cx, list, kid);
                    if (!ok)
                        break;
                }
            }
        }
    }

    return ok;
}
