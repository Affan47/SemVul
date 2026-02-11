Iterator(JSContext *cx, JSObject *iterobj, uintN argc, jsval *argv, jsval *rval)
{
    JSBool keyonly;
    uintN flags;
    JSObject *obj;

    keyonly = js_ValueToBoolean(argv[1]);
    flags = keyonly ? 0 : JSITER_FOREACH;

    if (JS_IsConstructing(cx)) {

        if (!JSVAL_IS_PRIMITIVE(argv[0])) {
            obj = JSVAL_TO_OBJECT(argv[0]);
        } else {
            obj = js_ValueToNonNullObject(cx, argv[0]);
            if (!obj)
                return JS_FALSE;
            argv[0] = OBJECT_TO_JSVAL(obj);
        }
        return InitNativeIterator(cx, iterobj, obj, flags);
    }

    *rval = argv[0];
    return js_ValueToIterator(cx, flags, rval);
}
