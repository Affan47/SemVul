JS_CloneFunctionObject(JSContext *cx, JSObject *funobj, JSObject *parent)
{
    CHECK_REQUEST(cx);
    if (OBJ_GET_CLASS(cx, funobj) != &js_FunctionClass) {


        jsval v = OBJECT_TO_JSVAL(funobj);
        js_ReportIsNotFunction(cx, &v, 0);
        return NULL;
    }

    JSFunction *fun = GET_FUNCTION_PRIVATE(cx, funobj);
    JSObject *clone = js_CloneFunctionObject(cx, fun, parent);
    if (!clone)
        return NULL;


    if (FUN_FLAT_CLOSURE(fun)) {
        JS_ASSERT(funobj->dslots);
        if (!js_EnsureReservedSlots(cx, clone,
                                    fun->countInterpretedReservedSlots())) {
            return NULL;
        }

        JSUpvarArray *uva = fun->u.i.script->upvars();
        JS_ASSERT(uva->length <= size_t(clone->dslots[-1]));

        void *mark = JS_ARENA_MARK(&cx->tempPool);
        jsuword *names = js_GetLocalNameArray(cx, fun, &cx->tempPool);
        if (!names)
            return NULL;

        uint32 i = 0, n = uva->length;
        for (; i < n; i++) {
            JSObject *obj = parent;
            int skip = UPVAR_FRAME_SKIP(uva->vector[i]);
            while (--skip > 0) {
                if (!obj) {
                    JS_ReportErrorNumber(cx, js_GetErrorMessage, NULL,
                                         JSMSG_BAD_CLONE_FUNOBJ_SCOPE);
                    goto break2;
                }
                obj = OBJ_GET_PARENT(cx, obj);
            }

            JSAtom *atom = JS_LOCAL_NAME_TO_ATOM(names[i]);
            if (!obj->getProperty(cx, ATOM_TO_JSID(atom), &clone->dslots[i]))
                break;
        }

      break2:
        JS_ARENA_RELEASE(&cx->tempPool, mark);
        if (i < n)
            return NULL;
    }

    return clone;
}
