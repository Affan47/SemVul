js_ValueToFunction(JSContext *cx, jsval *vp, uintN flags)
{
    jsval v;
    JSObject *obj;

    v = *vp;
    obj = NULL;
    if (JSVAL_IS_OBJECT(v)) {
        obj = JSVAL_TO_OBJECT(v);
        if (obj && OBJ_GET_CLASS(cx, obj) != &js_FunctionClass) {
            if (!obj->defaultValue(cx, JSTYPE_FUNCTION, &v))
                return NULL;
            obj = VALUE_IS_FUNCTION(cx, v) ? JSVAL_TO_OBJECT(v) : NULL;
        }
    }
    if (!obj) {
        js_ReportIsNotFunction(cx, vp, flags);
        return NULL;
    }
    return GET_FUNCTION_PRIVATE(cx, obj);
}
