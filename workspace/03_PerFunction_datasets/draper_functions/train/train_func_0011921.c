IteratorNextImpl(JSContext *cx, JSObject *obj, jsval *rval)
{
    JSObject *iterable;
    jsval state;
    uintN flags;
    JSBool foreach, ok;
    jsid id;

    JS_ASSERT(OBJ_GET_CLASS(cx, obj) == &js_IteratorClass);

    iterable = OBJ_GET_PARENT(cx, obj);
    JS_ASSERT(iterable);
    state = STOBJ_GET_SLOT(obj, JSSLOT_ITER_STATE);
    if (JSVAL_IS_NULL(state))
        goto stop;

    flags = JSVAL_TO_INT(STOBJ_GET_SLOT(obj, JSSLOT_ITER_FLAGS));
    JS_ASSERT(!(flags & JSITER_ENUMERATE));
    foreach = (flags & JSITER_FOREACH) != 0;
    ok =
#if JS_HAS_XML_SUPPORT
         (foreach && OBJECT_IS_XML(cx, iterable))
         ? js_EnumerateXMLValues(cx, iterable, JSENUMERATE_NEXT, &state,
                                 &id, rval)
         :
#endif
           iterable->enumerate(cx, JSENUMERATE_NEXT, &state, &id);
    if (!ok)
        return JS_FALSE;

    STOBJ_SET_SLOT(obj, JSSLOT_ITER_STATE, state);
    if (JSVAL_IS_NULL(state))
        goto stop;

    if (foreach) {
#if JS_HAS_XML_SUPPORT
        if (!OBJECT_IS_XML(cx, iterable) &&
            !iterable->getProperty(cx, id, rval)) {
            return JS_FALSE;
        }
#endif
        if (!NewKeyValuePair(cx, id, *rval, rval))
            return JS_FALSE;
    } else {
        *rval = ID_TO_VALUE(id);
    }
    return JS_TRUE;

  stop:
    JS_ASSERT(STOBJ_GET_SLOT(obj, JSSLOT_ITER_STATE) == JSVAL_NULL);
    *rval = JSVAL_HOLE;
    return JS_TRUE;
}
