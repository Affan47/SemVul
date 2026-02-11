js_NewFunction(JSContext *cx, JSObject *funobj, JSNative native, uintN nargs,
               uintN flags, JSObject *parent, JSAtom *atom)
{
    JSFunction *fun;

    if (funobj) {
        JS_ASSERT(HAS_FUNCTION_CLASS(funobj));
        OBJ_SET_PARENT(cx, funobj, parent);
    } else {
        funobj = js_NewObject(cx, &js_FunctionClass, NULL, parent);
        if (!funobj)
            return NULL;
    }
    JS_ASSERT(!funobj->getPrivate());
    fun = (JSFunction *) funobj;


    fun->nargs = nargs;
    fun->flags = flags & (JSFUN_FLAGS_MASK | JSFUN_KINDMASK | JSFUN_TRCINFO);
    if ((flags & JSFUN_KINDMASK) >= JSFUN_INTERPRETED) {
        JS_ASSERT(!native);
        JS_ASSERT(nargs == 0);
        fun->u.i.nvars = 0;
        fun->u.i.nupvars = 0;
        fun->u.i.skipmin = 0;
        fun->u.i.wrapper = false;
        fun->u.i.script = NULL;
#ifdef DEBUG
        fun->u.i.names.taggedAtom = 0;
#endif
    } else {
        fun->u.n.extra = 0;
        fun->u.n.spare = 0;
        fun->u.n.clasp = NULL;
        if (flags & JSFUN_TRCINFO) {
#ifdef JS_TRACER
            JSNativeTraceInfo *trcinfo =
                JS_FUNC_TO_DATA_PTR(JSNativeTraceInfo *, native);
            fun->u.n.native = (JSNative) trcinfo->native;
            fun->u.n.trcinfo = trcinfo;
#else
            fun->u.n.trcinfo = NULL;
#endif
        } else {
            fun->u.n.native = native;
            fun->u.n.trcinfo = NULL;
        }
        JS_ASSERT(fun->u.n.native);
    }
    fun->atom = atom;


    FUN_OBJECT(fun)->setPrivate(fun);
    return fun;
}
