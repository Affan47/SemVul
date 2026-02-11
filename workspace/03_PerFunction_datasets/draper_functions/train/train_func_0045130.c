js_NativeGet(JSContext *cx, JSObject *obj, JSObject *pobj,
             JSScopeProperty *sprop, jsval *vp)
{
    js_LeaveTraceIfGlobalObject(cx, pobj);

    JSScope *scope;
    uint32 slot;
    int32 sample;
    JSTempValueRooter tvr, tvr2;
    JSBool ok;

    JS_ASSERT(OBJ_IS_NATIVE(pobj));
    JS_ASSERT(JS_IS_OBJ_LOCKED(cx, pobj));
    scope = OBJ_SCOPE(pobj);

    slot = sprop->slot;
    *vp = (slot != SPROP_INVALID_SLOT)
          ? LOCKED_OBJ_GET_SLOT(pobj, slot)
          : JSVAL_VOID;
    if (SPROP_HAS_STUB_GETTER(sprop))
        return JS_TRUE;

    sample = cx->runtime->propertyRemovals;
    JS_UNLOCK_SCOPE(cx, scope);
    JS_PUSH_TEMP_ROOT_SPROP(cx, sprop, &tvr);
    JS_PUSH_TEMP_ROOT_OBJECT(cx, pobj, &tvr2);
    ok = js_GetSprop(cx, sprop, obj, vp);
    JS_POP_TEMP_ROOT(cx, &tvr2);
    JS_POP_TEMP_ROOT(cx, &tvr);
    if (!ok)
        return JS_FALSE;

    JS_LOCK_SCOPE(cx, scope);
    if (SLOT_IN_SCOPE(slot, scope) &&
        (JS_LIKELY(cx->runtime->propertyRemovals == sample) ||
         scope->has(sprop))) {
        LOCKED_OBJ_SET_SLOT(pobj, slot, *vp);
    }

    return JS_TRUE;
}
