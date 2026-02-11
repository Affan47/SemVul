num_parseInt(JSContext *cx, uintN argc, jsval *vp)
{
    jsint radix;
    JSString *str;
    jsdouble d;
    const jschar *bp, *end, *ep;

    if (argc == 0) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }
    if (argc > 1) {
        radix = js_ValueToECMAInt32(cx, &vp[3]);
        if (JSVAL_IS_NULL(vp[3]))
            return JS_FALSE;
    } else {
        radix = 0;
    }
    if (radix != 0 && (radix < 2 || radix > 36)) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }

    if (JSVAL_IS_INT(vp[2]) && (radix == 0 || radix == 10)) {
        *vp = vp[2];
        return JS_TRUE;
    }

    str = js_ValueToString(cx, vp[2]);
    if (!str)
        return JS_FALSE;
    str->getCharsAndEnd(bp, end);
    if (!js_strtointeger(cx, bp, end, &ep, radix, &d))
        return JS_FALSE;
    if (ep == bp) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }
    return js_NewNumberInRootedValue(cx, d, vp);
}
