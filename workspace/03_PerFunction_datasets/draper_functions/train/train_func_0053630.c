Append(JSContext *cx, JSXML *list, JSXML *xml)
{
    uint32 i, j, k, n;
    JSXML *kid;

    JS_ASSERT(list->xml_class == JSXML_CLASS_LIST);
    i = list->xml_kids.length;
    n = 1;
    if (xml->xml_class == JSXML_CLASS_LIST) {
        list->xml_target = xml->xml_target;
        list->xml_targetprop = xml->xml_targetprop;
        n = JSXML_LENGTH(xml);
        k = i + n;
        if (!XMLArraySetCapacity(cx, &list->xml_kids, k))
            return JS_FALSE;
        for (j = 0; j < n; j++) {
            kid = XMLARRAY_MEMBER(&xml->xml_kids, j, JSXML);
            if (kid)
                XMLARRAY_SET_MEMBER(&list->xml_kids, i + j, kid);
        }
        return JS_TRUE;
    }

    list->xml_target = xml->parent;
    if (xml->xml_class == JSXML_CLASS_PROCESSING_INSTRUCTION)
        list->xml_targetprop = NULL;
    else
        list->xml_targetprop = xml->name;
    if (!XMLARRAY_ADD_MEMBER(cx, &list->xml_kids, i, xml))
        return JS_FALSE;
    return JS_TRUE;
}
