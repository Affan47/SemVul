js_Construct(JSContext *cx, JSObject *obj, uintN argc, jsval *argv,
             jsval *rval)
{
    JSClass *clasp;

    clasp = OBJ_GET_CLASS(cx, JSVAL_TO_OBJECT(argv[-2]));
    if (!clasp->construct) {
#ifdef NARCISSUS
        JSObject *callee, *args;
        jsval cval, nargv[2];
        JSBool ok;

        callee = JSVAL_TO_OBJECT(argv[-2]);
        if (!callee->getProperty(cx, ATOM_TO_JSID(cx->runtime->atomState.__construct__Atom),
                                 &cval)) {
            return JS_FALSE;
        }
        if (VALUE_IS_FUNCTION(cx, cval)) {
            if (!GetCurrentExecutionContext(cx, obj, &nargv[1]))
                return JS_FALSE;
            args = js_GetArgsObject(cx, js_GetTopStackFrame(cx));
            if (!args)
                return JS_FALSE;
            nargv[0] = OBJECT_TO_JSVAL(args);
            return js_InternalCall(cx, callee, cval, 2, nargv, rval);
        }
        if (JSVAL_IS_OBJECT(cval) && JSVAL_TO_OBJECT(cval) != callee) {
            argv[-2] = cval;
            ok = js_Call(cx, obj, argc, argv, rval);
            argv[-2] = OBJECT_TO_JSVAL(callee);
            return ok;
        }
#endif
        js_ReportIsNotFunction(cx, &argv[-2], JSV2F_CONSTRUCT);
        return JS_FALSE;
    }
    return clasp->construct(cx, obj, argc, argv, rval);
}
