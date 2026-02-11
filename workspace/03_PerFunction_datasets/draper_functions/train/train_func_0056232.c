block_setProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    JS_ASSERT(obj->getClass() == &js_BlockClass);
    JS_ASSERT(OBJ_IS_CLONED_BLOCK(obj));
    uintN index = (uintN) JSVAL_TO_INT(id);
    JS_ASSERT(index < OBJ_BLOCK_COUNT(cx, obj));

    JSStackFrame *fp = (JSStackFrame *) obj->getPrivate();
    if (fp) {
        index += fp->script->nfixed + OBJ_BLOCK_DEPTH(cx, obj);
        JS_ASSERT(index < fp->script->nslots);
        fp->slots[index] = *vp;
        return true;
    }


    uint32 slot = JSSLOT_BLOCK_DEPTH + 1 + index;
    JS_LOCK_OBJ(cx, obj);
    JS_ASSERT(slot < STOBJ_NSLOTS(obj));
    STOBJ_SET_SLOT(obj, slot, *vp);
    JS_UNLOCK_OBJ(cx, obj);
    return true;
}
