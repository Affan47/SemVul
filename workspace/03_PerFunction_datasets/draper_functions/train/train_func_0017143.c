js_IndexToId(JSContext *cx, jsuint index, jsid *idp)
{
    JSString *str;

    if (index <= JSVAL_INT_MAX) {
        *idp = INT_TO_JSID(index);
        return JS_TRUE;
    }
    str = js_NumberToString(cx, index);
    if (!str)
        return JS_FALSE;
    return js_ValueToStringId(cx, STRING_TO_JSVAL(str), idp);
}
