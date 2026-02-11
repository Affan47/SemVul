js_NativeSet(JSContext *cx, JSObject *obj, JSScopeProperty *sprop, jsval *vp)
{
    js_LeaveTraceIfGlobalObject(cx, obj);

    JSScope *scope;
    uint32 slot;
    int32 sample;
    JSTempValueRooter tvr;
    JSBool ok;

    JS_ASSERT(OBJ_IS_NATIVE(obj));
    JS_ASSERT(JS_IS_OBJ_LOCKED(cx, obj));
    scope = OBJ_SCOPE(obj);

    slot = sprop->slot;
    if (slot != SPROP_INVALID_SLOT) {
        OBJ_CHECK_SLOT(obj, slot);


        if (SPROP_HAS_STUB_SETTER(sprop))
            goto set_slot;
    } else {


        if (SPROP_HAS_STUB_SETTER(sprop))
            return JS_TRUE;
    }

    sample = cx->runtime->propertyRemovals;
    JS_UNLOCK_SCOPE(cx, scope);
    JS_PUSH_TEMP_ROOT_SPROP(cx, sprop, &tvr);
    ok = js_SetSprop(cx, sprop, obj, vp);
    JS_POP_TEMP_ROOT(cx, &tvr);
    if (!ok)
        return JS_FALSE;

    JS_LOCK_SCOPE(cx, scope);
    if (SLOT_IN_SCOPE(slot, scope) &&
        (JS_LIKELY(cx->runtime->propertyRemovals == sample) ||
         scope->has(sprop))) {
  set_slot:
        LOCKED_OBJ_WRITE_SLOT(cx, obj, slot, *vp);
    }

    return JS_TRUE;
}
