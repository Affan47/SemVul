js_GetArgsProperty(JSContext *cx, JSStackFrame *fp, jsid id, jsval *vp)
{
    if (fp->flags & JSFRAME_OVERRIDE_ARGS) {
        JS_ASSERT(fp->callobj);

        jsid argumentsid = ATOM_TO_JSID(cx->runtime->atomState.argumentsAtom);
        jsval v;
        if (!fp->callobj->getProperty(cx, argumentsid, &v))
            return false;

        JSObject *obj;
        if (JSVAL_IS_PRIMITIVE(v)) {
            obj = js_ValueToNonNullObject(cx, v);
            if (!obj)
                return false;
        } else {
            obj = JSVAL_TO_OBJECT(v);
        }
        return obj->getProperty(cx, id, vp);
    }

    *vp = JSVAL_VOID;
    if (JSID_IS_INT(id)) {
        uint32 arg = uint32(JSID_TO_INT(id));
        JSObject *argsobj = JSVAL_TO_OBJECT(fp->argsobj);
        if (arg < fp->argc) {
            if (argsobj) {
                jsval v = OBJ_GET_SLOT(cx, argsobj, JSSLOT_ARGS_COPY_START+arg);
                if (v == JSVAL_HOLE)
                    return argsobj->getProperty(cx, id, vp);
            }
            *vp = fp->argv[arg];
        } else {


            if (argsobj)
                return argsobj->getProperty(cx, id, vp);
        }
    } else if (id == ATOM_TO_JSID(cx->runtime->atomState.lengthAtom)) {
        JSObject *argsobj = JSVAL_TO_OBJECT(fp->argsobj);
        if (argsobj && js_IsOverriddenArgsLength(argsobj))
            return argsobj->getProperty(cx, id, vp);
        *vp = INT_TO_JSVAL(jsint(fp->argc));
    }
    return true;
}
