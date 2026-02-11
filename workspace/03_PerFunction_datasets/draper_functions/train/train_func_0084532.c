namespace_equality(JSContext *cx, JSObject *obj, jsval v, JSBool *bp)
{
    JSObject *obj2;

    JS_ASSERT(JSVAL_IS_OBJECT(v));
    obj2 = JSVAL_TO_OBJECT(v);
    *bp = (!obj2 || OBJ_GET_CLASS(cx, obj2) != &js_NamespaceClass.base)
          ? JS_FALSE
          : js_EqualStrings(GetURI(obj), GetURI(obj2));
    return JS_TRUE;
}
