GetXMLFunction(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
{
    JSObject *target;
    JSXML *xml;
    JSTempValueRooter tvr;
    JSBool ok;

    JS_ASSERT(OBJECT_IS_XML(cx, obj));

    MUST_FLOW_THROUGH("out");
    JS_PUSH_TEMP_ROOT_OBJECT(cx, NULL, &tvr);


    target = obj;
    for (;;) {
        ok = js_GetProperty(cx, target, id, vp);
        if (!ok)
            goto out;
        if (VALUE_IS_FUNCTION(cx, *vp)) {
            ok = JS_TRUE;
            goto out;
        }
        target = OBJ_GET_PROTO(cx, target);
        if (target == NULL)
            break;
        tvr.u.object = target;
    }

    xml = (JSXML *) obj->getPrivate();
    if (HasSimpleContent(xml)) {

        ok = js_GetClassPrototype(cx, NULL, INT_TO_JSID(JSProto_String),
                                  &tvr.u.object);
        if (!ok)
            goto out;
        JS_ASSERT(tvr.u.object);
        ok = tvr.u.object->getProperty(cx, id, vp);
    }

  out:
    JS_POP_TEMP_ROOT(cx, &tvr);
    return ok;
}
