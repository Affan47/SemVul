JS_AliasElement(JSContext *cx, JSObject *obj, const char *name, jsint alias)
{
    JSObject *obj2;
    JSProperty *prop;
    JSScopeProperty *sprop;
    JSBool ok;

    CHECK_REQUEST(cx);
    if (!LookupProperty(cx, obj, name, JSRESOLVE_QUALIFIED, &obj2, &prop))
        return JS_FALSE;
    if (!prop) {
        js_ReportIsNotDefined(cx, name);
        return JS_FALSE;
    }
    if (obj2 != obj || !OBJ_IS_NATIVE(obj)) {
        char numBuf[12];
        obj2->dropProperty(cx, prop);
        JS_snprintf(numBuf, sizeof numBuf, "%ld", (long)alias);
        JS_ReportErrorNumber(cx, js_GetErrorMessage, NULL, JSMSG_CANT_ALIAS,
                             numBuf, name, OBJ_GET_CLASS(cx, obj2)->name);
        return JS_FALSE;
    }
    sprop = (JSScopeProperty *)prop;
    ok = (js_AddNativeProperty(cx, obj, INT_TO_JSID(alias),
                               sprop->getter, sprop->setter, sprop->slot,
                               sprop->attrs, sprop->flags | SPROP_IS_ALIAS,
                               sprop->shortid)
          != NULL);
    obj->dropProperty(cx, prop);
    return ok;
}
