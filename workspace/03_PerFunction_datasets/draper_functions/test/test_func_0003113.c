js_HasLengthProperty(JSContext *cx, JSObject *obj, jsuint *lengthp)
{
    JSErrorReporter older = JS_SetErrorReporter(cx, NULL);
    JSAutoTempValueRooter tvr(cx, JSVAL_NULL);
    jsid id = ATOM_TO_JSID(cx->runtime->atomState.lengthAtom);
    JSBool ok = obj->getProperty(cx, id, tvr.addr());
    JS_SetErrorReporter(cx, older);
    if (!ok)
        return false;

    *lengthp = ValueIsLength(cx, tvr.addr());
    return !JSVAL_IS_NULL(tvr.value());
}
