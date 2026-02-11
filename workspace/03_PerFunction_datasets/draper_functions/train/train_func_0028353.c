js_GetLengthProperty(JSContext *cx, JSObject *obj, jsuint *lengthp)
{
    if (OBJ_IS_ARRAY(cx, obj)) {
        *lengthp = obj->fslots[JSSLOT_ARRAY_LENGTH];
        return JS_TRUE;
    }

    JSAutoTempValueRooter tvr(cx, JSVAL_NULL);
    if (!obj->getProperty(cx, ATOM_TO_JSID(cx->runtime->atomState.lengthAtom), tvr.addr()))
        return JS_FALSE;

    if (JSVAL_IS_INT(tvr.value())) {
        *lengthp = jsuint(jsint(JSVAL_TO_INT(tvr.value())));
        return JS_TRUE;
    }

    *lengthp = js_ValueToECMAUint32(cx, tvr.addr());
    return !JSVAL_IS_NULL(tvr.value());
}
