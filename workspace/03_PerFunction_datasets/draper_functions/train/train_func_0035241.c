js_fun_apply(JSContext *cx, uintN argc, jsval *vp)
{
    JSObject *obj, *aobj;
    jsval fval, *invokevp, *sp;
    JSString *str;
    jsuint length;
    JSBool arraylike, ok;
    void *mark;
    uintN i;

    if (argc == 0) {

        return js_fun_call(cx, argc, vp);
    }

    js_LeaveTrace(cx);

    obj = JS_THIS_OBJECT(cx, vp);
    if (!obj || !obj->defaultValue(cx, JSTYPE_FUNCTION, &vp[1]))
        return JS_FALSE;
    fval = vp[1];

    if (!VALUE_IS_FUNCTION(cx, fval)) {
        str = JS_ValueToString(cx, fval);
        if (str) {
            const char *bytes = js_GetStringBytes(cx, str);

            if (bytes) {
                JS_ReportErrorNumber(cx, js_GetErrorMessage, NULL,
                                     JSMSG_INCOMPATIBLE_PROTO,
                                     js_Function_str, js_apply_str,
                                     bytes);
            }
        }
        return JS_FALSE;
    }


    aobj = NULL;
    length = 0;

    if (argc >= 2) {

        if (JSVAL_IS_NULL(vp[3]) || JSVAL_IS_VOID(vp[3])) {
            argc = 0;
        } else {

            arraylike = JS_FALSE;
            if (!JSVAL_IS_PRIMITIVE(vp[3])) {
                aobj = JSVAL_TO_OBJECT(vp[3]);
                if (!js_IsArrayLike(cx, aobj, &arraylike, &length))
                    return JS_FALSE;
            }
            if (!arraylike) {
                JS_ReportErrorNumber(cx, js_GetErrorMessage, NULL,
                                     JSMSG_BAD_APPLY_ARGS, js_apply_str);
                return JS_FALSE;
            }
        }
    }


    if (!JSVAL_IS_PRIMITIVE(vp[2]))
        obj = JSVAL_TO_OBJECT(vp[2]);
    else if (!js_ValueToObject(cx, vp[2], &obj))
        return JS_FALSE;


    argc = (uintN)JS_MIN(length, JS_ARGS_LENGTH_MAX);
    invokevp = js_AllocStack(cx, 2 + argc, &mark);
    if (!invokevp)
        return JS_FALSE;


    sp = invokevp;
    *sp++ = fval;
    *sp++ = OBJECT_TO_JSVAL(obj);
    for (i = 0; i < argc; i++) {
        ok = JS_GetElement(cx, aobj, (jsint)i, sp);
        if (!ok)
            goto out;
        sp++;
    }

    ok = js_Invoke(cx, argc, invokevp, 0);
    *vp = *invokevp;
out:
    js_FreeStack(cx, mark);
    return ok;
}
