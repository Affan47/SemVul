js_NumberToString(JSContext *cx, jsdouble d)
{
    jsint i;

    if (JSDOUBLE_IS_INT(d, i) && jsuint(i) < INT_STRING_LIMIT)
        return JSString::intString(i);
    return NumberToStringWithBase(cx, d, 10);
}
