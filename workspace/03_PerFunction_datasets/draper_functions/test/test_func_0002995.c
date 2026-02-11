findInvokeDynamicInvoker(Class *class,
                                                 char *methodname,
                                                 char *type,
                                                 int boot_mthd_idx) {
    Object *exception;
    Object *boot_mthd;
    Object *method_type;
    Object *member_name;
    Object *appendix_box;
    PolyMethodBlock *pmb;
    Object *args_array = NULL;
    ClassBlock *cb = CLASS_CB(class);
    ConstantPool *cp = &cb->constant_pool;
    Class *obj_array_class = findArrayClass("[Ljava/lang/Object;");
    Object *name_str = findInternedString(createString(methodname));
    int mthd_idx = BOOTSTRAP_METHOD_REF(cb->bootstrap_methods, boot_mthd_idx);
    int args = BOOTSTRAP_METHOD_ARG_COUNT(cb->bootstrap_methods, boot_mthd_idx);

    if(args != 0) {
        Object **args_data;
        int i;

        args_array = allocArray(obj_array_class, args, sizeof(Object*));
        if(args_array == NULL)
            return NULL;

        args_data = ARRAY_DATA(args_array, Object*);

        for(i = 0; i < args; i++) {
            int idx = BOOTSTRAP_METHOD_ARG(cb->bootstrap_methods,
                                           boot_mthd_idx, i);
            int prim_idx = cpType2PrimIdx(CP_TYPE(cp, idx));

            if(prim_idx != -1)
                args_data[i] = createWrapperObject(prim_idx,
                                                   &CP_INFO(cp, idx),
                                                   REF_SRC_FIELD);
            else
                args_data[i] = (Object*)resolveSingleConstant(class, idx);

            if(args_data[i] == NULL)
                return NULL;
        }
    }

    appendix_box = allocArray(obj_array_class, 1, sizeof(Object*));
    if(appendix_box == NULL)
        return NULL;

    method_type = findMethodHandleType(type, class);
    if(method_type == NULL)
        return NULL;

    boot_mthd = resolveMethodHandle(class, mthd_idx);
    if(boot_mthd == NULL)
        return NULL;

    member_name = *(Object**)executeStaticMethod(MHN_linkCallSite_mb->class,
                                                 MHN_linkCallSite_mb,
                                                 class, boot_mthd, name_str,
                                                 method_type, args_array,
                                                 appendix_box);


    if((exception = exceptionOccurred())) {
        if(!isSubClassOf(EXCEPTION(java_lang_BootstrapMethodError),
                         exception) &&
           isSubClassOf(EXCEPTION(java_lang_LinkageError), exception)) {
            clearException();
            signalChainedException(java_lang_BootstrapMethodError,
                                   NULL, exception);
        }
        return NULL;
    }

    pmb = sysMalloc(sizeof(PolyMethodBlock));
    pmb->appendix = ARRAY_DATA(appendix_box, Object*)[0];
    pmb->mb = INST_DATA(member_name, MethodBlock*, mem_name_vmtarget_offset);

    return pmb;
}
