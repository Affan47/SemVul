obj_watch(JSContext *cx, uintN argc, jsval *vp)
{
    JSObject *callable;
    jsval userid, value;
    jsid propid;
    JSObject *obj;
    uintN attrs;

    if (argc <= 1) {
        js_ReportMissingArg(cx, vp, 1);
        return JS_FALSE;
    }

    callable = js_ValueToCallableObject(cx, &vp[3], 0);
    if (!callable)
        return JS_FALSE;


    userid = vp[2];
    if (!JS_ValueToId(cx, userid, &propid))
        return JS_FALSE;

    obj = JS_THIS_OBJECT(cx, vp);
    if (!obj || !obj->checkAccess(cx, propid, JSACC_WATCH, &value, &attrs))
        return JS_FALSE;
    if (attrs & JSPROP_READONLY)
        return JS_TRUE;
    *vp = JSVAL_VOID;

    if (OBJ_IS_DENSE_ARRAY(cx, obj) && !js_MakeArraySlow(cx, obj))
        return JS_FALSE;
    return JS_SetWatchPoint(cx, obj, userid, obj_watch_handler, callable);
}
