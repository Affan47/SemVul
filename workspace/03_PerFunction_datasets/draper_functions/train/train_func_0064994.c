resolveMethod(Class *class, int cp_index) {
    ConstantPool *cp = &(CLASS_CB(class)->constant_pool);
    MethodBlock *mb = NULL;
    int tag;

retry:
    tag = CP_TYPE(cp, cp_index);
    switch(tag) {
        case CONSTANT_Locked:
            goto retry;

        case CONSTANT_ResolvedMethod:
            mb = (MethodBlock *)CP_INFO(cp, cp_index);
            break;

        case CONSTANT_Methodref:
        case CONSTANT_InterfaceMethodref: {
            Class *resolved_class;
            ClassBlock *resolved_cb;
            char *methodname, *methodtype;
            int cl_idx = CP_METHOD_CLASS(cp, cp_index);
            int name_type_idx = CP_METHOD_NAME_TYPE(cp, cp_index);

            MBARRIER();
            if(CP_TYPE(cp, cp_index) != tag)
                goto retry;

            methodname = CP_UTF8(cp, CP_NAME_TYPE_NAME(cp, name_type_idx));

            methodtype = CP_UTF8(cp, CP_NAME_TYPE_TYPE(cp, name_type_idx));
            resolved_class = resolveClass(class, cl_idx, TRUE, FALSE);
            resolved_cb = CLASS_CB(resolved_class);

            if(exceptionOccurred())
                return NULL;

            if(resolved_cb->access_flags & ACC_INTERFACE) {
#ifdef JSR335
                mb = lookupInterfaceMethod(resolved_class, methodname,
                	                   methodtype);
#else
                signalException(java_lang_IncompatibleClassChangeError, NULL);
                return NULL;
#endif
            } else
                mb = lookupMethod(resolved_class, methodname, methodtype);

#ifdef JSR292
            if(mb == NULL)
                mb = lookupPolymorphicMethod(resolved_class, class,
                                             methodname, methodtype);
#endif

            if(mb != NULL) {
                if((mb->access_flags & ACC_ABSTRACT) &&
                       !(resolved_cb->access_flags & ACC_ABSTRACT)) {
                    signalException(java_lang_AbstractMethodError, methodname);
                    return NULL;
                }

                if(!checkMethodAccess(mb, class)) {
                    signalException(java_lang_IllegalAccessError,
                                    "method is not accessible");
                    return NULL;
                }

                if(initClass(mb->class) == NULL)
                    return NULL;

                CP_TYPE(cp, cp_index) = CONSTANT_Locked;
                MBARRIER();
                CP_INFO(cp, cp_index) = (uintptr_t)mb;
                MBARRIER();
                CP_TYPE(cp, cp_index) = CONSTANT_ResolvedMethod;
            } else
                signalException(java_lang_NoSuchMethodError, methodname);

            break;
        }
    }

    return mb;
}
