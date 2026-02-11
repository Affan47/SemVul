fun_enumerate(JSContext *cx, JSObject *obj)
{
    jsid prototypeId;
    JSObject *pobj;
    JSProperty *prop;

    prototypeId = ATOM_TO_JSID(cx->runtime->atomState.classPrototypeAtom);
    if (!obj->lookupProperty(cx, prototypeId, &pobj, &prop))
        return JS_FALSE;
    if (prop)
        pobj->dropProperty(cx, prop);
    return JS_TRUE;
}
