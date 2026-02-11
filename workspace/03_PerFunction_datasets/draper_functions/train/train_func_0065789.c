JS_GetUCPropertyAttrsGetterAndSetter(JSContext *cx, JSObject *obj,
                                     const jschar *name, size_t namelen,
                                     uintN *attrsp, JSBool *foundp,
                                     JSPropertyOp *getterp,
                                     JSPropertyOp *setterp)
{
    CHECK_REQUEST(cx);
    return GetPropertyAttributes(cx, obj,
                    js_AtomizeChars(cx, name, AUTO_NAMELEN(name, namelen), 0),
                    attrsp, foundp, getterp, setterp);
}
