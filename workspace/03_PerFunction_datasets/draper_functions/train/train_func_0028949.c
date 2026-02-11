ToAttributeName(JSContext *cx, jsval v)
{
    JSString *name, *uri, *prefix;
    JSObject *obj;
    JSClass *clasp;
    JSObject *qn;

    if (JSVAL_IS_STRING(v)) {
        name = JSVAL_TO_STRING(v);
        uri = prefix = cx->runtime->emptyString;
    } else {
        if (JSVAL_IS_PRIMITIVE(v)) {
            js_ReportValueError(cx, JSMSG_BAD_XML_ATTR_NAME,
                                JSDVG_IGNORE_STACK, v, NULL);
            return NULL;
        }

        obj = JSVAL_TO_OBJECT(v);
        clasp = OBJ_GET_CLASS(cx, obj);
        if (clasp == &js_AttributeNameClass)
            return obj;

        if (clasp == &js_QNameClass.base) {
            qn = obj;
            uri = GetURI(qn);
            prefix = GetPrefix(qn);
            name = GetLocalName(qn);
        } else {
            if (clasp == &js_AnyNameClass) {
                name = ATOM_TO_STRING(cx->runtime->atomState.starAtom);
            } else {
                name = js_ValueToString(cx, v);
                if (!name)
                    return NULL;
            }
            uri = prefix = cx->runtime->emptyString;
        }
    }

    qn = NewXMLQName(cx, uri, prefix, name, &js_AttributeNameClass);
    if (!qn)
        return NULL;
    return qn;
}
