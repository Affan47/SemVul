js_NewWithObject(JSContext *cx, JSObject *proto, JSObject *parent, jsint depth)
{
    JSObject *obj;

    obj = js_NewObject(cx, &js_WithClass, proto, parent);
    if (!obj)
        return NULL;
    obj->setPrivate(cx->fp);
    OBJ_SET_BLOCK_DEPTH(cx, obj, depth);
    return obj;
}
