HasFunctionProperty(JSContext *cx, JSObject *obj, jsid funid, JSBool *found)
{
    JSObject *pobj;
    JSProperty *prop;
    JSXML *xml;
    JSTempValueRooter tvr;
    JSBool ok;

    JS_ASSERT(OBJ_GET_CLASS(cx, obj) == &js_XMLClass);

    if (!js_LookupProperty(cx, obj, funid, &pobj, &prop))
        return JS_FALSE;
    if (prop) {
        pobj->dropProperty(cx, prop);
    } else {
        xml = (JSXML *) obj->getPrivate();
        if (HasSimpleContent(xml)) {


            JS_PUSH_TEMP_ROOT_OBJECT(cx, NULL, &tvr);
            ok = js_GetClassPrototype(cx, NULL, INT_TO_JSID(JSProto_String),
                                      &tvr.u.object);
            JS_ASSERT(tvr.u.object);
            if (ok) {
                ok = js_LookupProperty(cx, tvr.u.object, funid, &pobj, &prop);
                if (ok && prop)
                    pobj->dropProperty(cx, prop);
            }
            JS_POP_TEMP_ROOT(cx, &tvr);
            if (!ok)
                return JS_FALSE;
        }
    }
    *found = (prop != NULL);
    return JS_TRUE;
}
