defineAnonymousClass(Class *class, MethodBlock *mb,
	                        uintptr_t *ostack) {
    Class *host_class = (Class *)ostack[1];
    Object *data = (Object *)ostack[2];
    Object *cp_patches = (Object *)ostack[3];
    ClassBlock *host_cb = CLASS_CB(host_class);

    TRACE("defineAnonymousClass\n");

    class = parseClass(NULL, ARRAY_DATA(data, char), 0, ARRAY_LEN(data),
                       host_cb->class_loader);

    if(class != NULL) {
        int cp_patches_len = cp_patches == NULL ? 0 : ARRAY_LEN(cp_patches);
        ClassBlock *cb = CLASS_CB(class);
        ConstantPool *cp = &(cb->constant_pool);
        int i;

        for(i = 0; i < cp_patches_len; i++) {
            Object *obj = ARRAY_DATA(cp_patches, Object*)[i];
            if(obj != NULL) {
                int type = CP_TYPE(cp, i);

                switch(type) {
                    case CONSTANT_String:
                        CP_INFO(cp, i) = (uintptr_t)obj;
                        CP_TYPE(cp, i) = CONSTANT_ResolvedString;
                        break;

                    default:
                        signalException(java_lang_InternalError,
                                        "defineAnonymousClass: "
                                        "unimplemented patch type");
                }
            }
        }

        cb->protection_domain = host_cb->protection_domain;
    }

    *ostack++ = (uintptr_t) class;
    return ostack;
}
