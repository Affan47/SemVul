xml_namespaceDeclarations(JSContext *cx, uintN argc, jsval *vp)
{
    JSBool ok;
    JSTempRootedNSArray ancestors, declared;
    JSXML *yml;
    uint32 i, n;
    JSObject *ns;

    NON_LIST_XML_METHOD_PROLOG;
    if (JSXML_HAS_VALUE(xml))
        return JS_TRUE;


    ok = JS_TRUE;
    InitTempNSArray(cx, &ancestors);
    InitTempNSArray(cx, &declared);
    yml = xml;

    while ((yml = yml->parent) != NULL) {
        JS_ASSERT(yml->xml_class == JSXML_CLASS_ELEMENT);
        for (i = 0, n = yml->xml_namespaces.length; i < n; i++) {
            ns = XMLARRAY_MEMBER(&yml->xml_namespaces, i, JSObject);
            if (ns &&
                !XMLARRAY_HAS_MEMBER(&ancestors.array, ns, namespace_match)) {
                ok = XMLARRAY_APPEND(cx, &ancestors.array, ns);
                if (!ok)
                    goto out;
            }
        }
    }

    for (i = 0, n = xml->xml_namespaces.length; i < n; i++) {
        ns = XMLARRAY_MEMBER(&xml->xml_namespaces, i, JSObject);
        if (!ns)
            continue;
        if (!IsDeclared(ns))
            continue;
        if (!XMLARRAY_HAS_MEMBER(&ancestors.array, ns, namespace_match)) {
            ok = XMLARRAY_APPEND(cx, &declared.array, ns);
            if (!ok)
                goto out;
        }
    }

    ok = TempNSArrayToJSArray(cx, &declared, vp);

out:

    FinishTempNSArray(cx, &declared);
    FinishTempNSArray(cx, &ancestors);
    return ok;
}
