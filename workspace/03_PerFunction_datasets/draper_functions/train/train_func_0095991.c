FindInScopeNamespaces(JSContext *cx, JSXML *xml, JSXMLArray *nsarray)
{
    uint32 length, i, j, n;
    JSObject *ns, *ns2;
    JSString *prefix, *prefix2;

    length = nsarray->length;
    do {
        if (xml->xml_class != JSXML_CLASS_ELEMENT)
            continue;
        for (i = 0, n = xml->xml_namespaces.length; i < n; i++) {
            ns = XMLARRAY_MEMBER(&xml->xml_namespaces, i, JSObject);
            if (!ns)
                continue;

            prefix = GetPrefix(ns);
            for (j = 0; j < length; j++) {
                ns2 = XMLARRAY_MEMBER(nsarray, j, JSObject);
                if (ns2) {
                    prefix2 = GetPrefix(ns2);
                    if ((prefix2 && prefix)
                        ? js_EqualStrings(prefix2, prefix)
                        : js_EqualStrings(GetURI(ns2), GetURI(ns))) {
                        break;
                    }
                }
            }

            if (j == length) {
                if (!XMLARRAY_APPEND(cx, nsarray, ns))
                    return JS_FALSE;
                ++length;
            }
        }
    } while ((xml = xml->parent) != NULL);
    JS_ASSERT(length == nsarray->length);

    return JS_TRUE;
}
