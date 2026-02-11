js_ValueToBoolean(jsval v)
{
    if (JSVAL_IS_NULL(v) || JSVAL_IS_VOID(v))
        return JS_FALSE;
    if (JSVAL_IS_OBJECT(v))
        return JS_TRUE;
    if (JSVAL_IS_STRING(v))
        return JSVAL_TO_STRING(v)->length() != 0;
    if (JSVAL_IS_INT(v))
        return JSVAL_TO_INT(v) != 0;
    if (JSVAL_IS_DOUBLE(v)) {
        jsdouble d;

        d = *JSVAL_TO_DOUBLE(v);
        return !JSDOUBLE_IS_NaN(d) && d != 0;
    }
    JS_ASSERT(JSVAL_IS_BOOLEAN(v));
    return JSVAL_TO_BOOLEAN(v);
}
