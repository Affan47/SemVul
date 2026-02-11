bool_toString(JSContext *cx, uintN argc, jsval *vp)
{
    jsval v;
    JSAtom *atom;
    JSString *str;

    if (!js_GetPrimitiveThis(cx, vp, &js_BooleanClass, &v))
        return JS_FALSE;
    JS_ASSERT(JSVAL_IS_BOOLEAN(v));
    atom = cx->runtime->atomState.booleanAtoms[JSVAL_TO_BOOLEAN(v) ? 1 : 0];
    str = ATOM_TO_STRING(atom);
    if (!str)
        return JS_FALSE;
    *vp = STRING_TO_JSVAL(str);
    return JS_TRUE;
}
