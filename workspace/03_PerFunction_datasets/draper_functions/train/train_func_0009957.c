js_GetClassId(JSContext *cx, JSClass *clasp, jsid *idp)
{
    JSProtoKey key;
    JSAtom *atom;

    key = JSCLASS_CACHED_PROTO_KEY(clasp);
    if (key != JSProto_Null) {
        *idp = INT_TO_JSID(key);
    } else if (clasp->flags & JSCLASS_IS_ANONYMOUS) {
        *idp = INT_TO_JSID(JSProto_Object);
    } else {
        atom = js_Atomize(cx, clasp->name, strlen(clasp->name), 0);
        if (!atom)
            return JS_FALSE;
        *idp = ATOM_TO_JSID(atom);
    }
    return JS_TRUE;
}
