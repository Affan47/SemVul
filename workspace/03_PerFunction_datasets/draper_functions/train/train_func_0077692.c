JS_GetParent(JSContext *cx, JSObject *obj)
{
    JSObject *parent;

    parent = OBJ_GET_PARENT(cx, obj);


    return parent && parent->map ? parent : NULL;
}
