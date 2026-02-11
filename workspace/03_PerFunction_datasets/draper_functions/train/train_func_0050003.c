js_json_stringify(JSContext *cx, uintN argc, jsval *vp)
{
    jsval *argv = vp + 2;
    JSObject *replacer = NULL;
    jsval space = JSVAL_NULL;
    JSAutoTempValueRooter tvr(cx, replacer);
    JSAutoTempValueRooter tvr2(cx, 1, &space);


    if (!JS_ConvertArguments(cx, argc, argv, "v / o v", vp, &replacer, &space))
        return JS_FALSE;

    JSCharBuffer cb(cx);

    if (!js_Stringify(cx, vp, replacer, space, cb))
        return JS_FALSE;


    if (!cb.empty()) {
        JSString *str = js_NewStringFromCharBuffer(cx, cb);
        if (!str)
            return JS_FALSE;
        *vp = STRING_TO_JSVAL(str);
    } else {
        *vp = JSVAL_VOID;
    }

    return JS_TRUE;
}
