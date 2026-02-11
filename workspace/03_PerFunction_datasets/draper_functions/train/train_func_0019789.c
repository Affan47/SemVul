StackQuota(JSContext *cx, uintN argc, jsval *vp)
{
    uint32 n;

    if (argc == 0)
        return JS_NewNumberValue(cx, (double) gScriptStackQuota, vp);
    if (!JS_ValueToECMAUint32(cx, JS_ARGV(cx, vp)[0], &n))
        return JS_FALSE;
    gScriptStackQuota = n;
    JS_SetScriptStackQuota(cx, gScriptStackQuota);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}
