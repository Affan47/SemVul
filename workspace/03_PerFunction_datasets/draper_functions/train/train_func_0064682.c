JS_DefineProperties(JSContext *cx, JSObject *obj, JSPropertySpec *ps)
{
    JSBool ok;

    CHECK_REQUEST(cx);
    for (ok = JS_TRUE; ps->name; ps++) {
        ok = DefineProperty(cx, obj, ps->name, JSVAL_VOID,
                            ps->getter, ps->setter, ps->flags,
                            SPROP_HAS_SHORTID, ps->tinyid);
        if (!ok)
            break;
    }
    return ok;
}
