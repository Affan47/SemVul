invoke(Object *ob, MethodBlock *mb, Object *arg_array,
                Object *param_types) {

    Object **args = ARRAY_DATA(arg_array, Object*);
    Class **types = ARRAY_DATA(param_types, Class*);

    int types_len = ARRAY_LEN(param_types);
    int args_len = arg_array ? ARRAY_LEN(arg_array) : 0;

    ExecEnv *ee = getExecEnv();
    uintptr_t *sp;
    Object *excep;
    void *ret;
    int i;

    if(args_len != types_len) {
        signalException(java_lang_IllegalArgumentException,
                        "wrong number of args");
        return NULL;
    }

    CREATE_TOP_FRAME(ee, mb->class, mb, sp, ret);

    if(ob) *sp++ = (uintptr_t)ob;

    for(i = 0; i < args_len; i++) {
        int size = unwrapAndWidenObject(*types++, *args++, sp, REF_DST_OSTACK);

        if(size == 0) {
            POP_TOP_FRAME(ee);
            signalException(java_lang_IllegalArgumentException,
                            "arg type mismatch");
            return NULL;
        }

        sp += size;
    }

    if(mb->access_flags & ACC_SYNCHRONIZED)
        objectLock(ob ? ob : mb->class);

    if(mb->access_flags & ACC_NATIVE)
        (*mb->native_invoker)(mb->class, mb, ret);
    else
        executeJava();

    if(mb->access_flags & ACC_SYNCHRONIZED)
        objectUnlock(ob ? ob : mb->class);

    POP_TOP_FRAME(ee);

    if((excep = exceptionOccurred())) {
        Object *ite_excep;
        MethodBlock *init;
        Class *ite_class;

        clearException();
        ite_class = findSystemClass("java/lang/reflect/InvocationTargetException");

        if(!exceptionOccurred() && (ite_excep = allocObject(ite_class)) &&
                      (init = lookupMethod(ite_class, SYMBOL(object_init),
                                           SYMBOL(_java_lang_Throwable__V)))) {
            executeMethod(ite_excep, init, excep);
            setException(ite_excep);
        }
        return NULL;
    }

    return ret;
}
