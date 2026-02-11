js_ValueToFunctionObject(JSContext *cx, jsval *vp, uintN flags)
{
    JSFunction *fun;
    JSStackFrame *caller;
    JSPrincipals *principals;

    if (VALUE_IS_FUNCTION(cx, *vp))
        return JSVAL_TO_OBJECT(*vp);

    fun = js_ValueToFunction(cx, vp, flags);
    if (!fun)
        return NULL;
    *vp = OBJECT_TO_JSVAL(FUN_OBJECT(fun));

    caller = js_GetScriptedCaller(cx, NULL);
    if (caller) {
        principals = JS_StackFramePrincipals(cx, caller);
    } else {

        principals = NULL;
    }

    if (!js_CheckPrincipalsAccess(cx, FUN_OBJECT(fun), principals,
                                  fun->atom
                                  ? fun->atom
                                  : cx->runtime->atomState.anonymousAtom)) {
        return NULL;
    }
    return FUN_OBJECT(fun);
}
