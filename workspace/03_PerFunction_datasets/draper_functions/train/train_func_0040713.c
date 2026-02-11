str_substr(JSContext *cx, uintN argc, jsval *vp)
{
    JSString *str;
    jsdouble d;
    jsdouble length, begin, end;

    NORMALIZE_THIS(cx, vp, str);
    if (argc != 0) {
        d = js_ValueToNumber(cx, &vp[2]);
        if (JSVAL_IS_NULL(vp[2]))
            return JS_FALSE;
        length = str->length();
        begin = js_DoubleToInteger(d);
        if (begin < 0) {
            begin += length;
            if (begin < 0)
                begin = 0;
        } else if (begin > length) {
            begin = length;
        }

        if (argc == 1) {
            end = length;
        } else {
            d = js_ValueToNumber(cx, &vp[3]);
            if (JSVAL_IS_NULL(vp[3]))
                return JS_FALSE;
            end = js_DoubleToInteger(d);
            if (end < 0)
                end = 0;
            end += begin;
            if (end > length)
                end = length;
        }

        str = js_NewDependentString(cx, str,
                                    (size_t)begin,
                                    (size_t)(end - begin));
        if (!str)
            return JS_FALSE;
    }
    *vp = STRING_TO_JSVAL(str);
    return JS_TRUE;
}
