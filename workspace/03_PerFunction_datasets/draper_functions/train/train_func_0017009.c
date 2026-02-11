js_InitRegExpClass(JSContext *cx, JSObject *obj)
{
    JSObject *proto = js_InitClass(cx, obj, NULL, &js_RegExpClass, RegExp, 1,
                                   regexp_props, regexp_methods,
                                   regexp_static_props, NULL);
    if (!proto)
        return NULL;

    JSObject *ctor = JS_GetConstructor(cx, proto);
    if (!ctor)
        return NULL;


    jsval rval;
    if (!JS_AliasProperty(cx, ctor, "input",        "$_") ||
        !JS_AliasProperty(cx, ctor, "multiline",    "$*") ||
        !JS_AliasProperty(cx, ctor, "lastMatch",    "$&") ||
        !JS_AliasProperty(cx, ctor, "lastParen",    "$+") ||
        !JS_AliasProperty(cx, ctor, "leftContext",  "$`") ||
        !JS_AliasProperty(cx, ctor, "rightContext", "$'") ||
        !regexp_compile_sub(cx, proto, 0, NULL, &rval)) {
        return NULL;
    }

    return proto;
}
