js_CloneFunctionObject(JSContext *cx, JSFunction *fun, JSObject *parent)
{


    JSObject *clone = js_NewObject(cx, &js_FunctionClass, NULL, parent, sizeof(JSObject));
    if (!clone)
        return NULL;
    clone->setPrivate(fun);
    return clone;
}
