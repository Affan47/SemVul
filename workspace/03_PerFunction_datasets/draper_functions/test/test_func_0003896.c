str_charCodeAt(JSContext *cx, uintN argc, jsval *vp)
{
    jsval t;
    JSString *str;
    jsint i;
    jsdouble d;

    t = vp[1];
    if (JSVAL_IS_STRING(t) && argc != 0 && JSVAL_IS_INT(vp[2])) {
        str = JSVAL_TO_STRING(t);
        i = JSVAL_TO_INT(vp[2]);
        if ((size_t)i >= str->length())
            goto out_of_range;
    } else {
        str = NormalizeThis(cx, vp);
        if (!str)
            return JS_FALSE;

        if (argc == 0) {
            d = 0.0;
        } else {
            d = js_ValueToNumber(cx, &vp[2]);
            if (JSVAL_IS_NULL(vp[2]))
                return JS_FALSE;
            d = js_DoubleToInteger(d);
        }

        if (d < 0 || str->length() <= d)
            goto out_of_range;
        i = (jsint) d;
    }

    *vp = INT_TO_JSVAL(str->chars()[i]);
    return JS_TRUE;

out_of_range:
    *vp = JS_GetNaNValue(cx);
    return JS_TRUE;
}
