resolveSingleConstant(Class *class, int cp_index) {
    ConstantPool *cp = &(CLASS_CB(class)->constant_pool);

retry:
    switch(CP_TYPE(cp, cp_index)) {
        case CONSTANT_Locked:
            goto retry;

        case CONSTANT_Class:
            resolveClass(class, cp_index, TRUE, FALSE);
            break;

#ifdef JSR292
        case CONSTANT_MethodType:
            resolveMethodType(class, cp_index);
            break;

        case CONSTANT_MethodHandle:
            resolveMethodHandle(class, cp_index);
            break;
#endif

        case CONSTANT_String: {
            Object *string;
            int idx = CP_STRING(cp, cp_index);

            MBARRIER();
            if(CP_TYPE(cp, cp_index) != CONSTANT_String)
                goto retry;

            string = createString(CP_UTF8(cp, idx));

            if(string) {
                CP_TYPE(cp, cp_index) = CONSTANT_Locked;
                MBARRIER();
                CP_INFO(cp, cp_index) = (uintptr_t)findInternedString(string);
                MBARRIER();
                CP_TYPE(cp, cp_index) = CONSTANT_ResolvedString;
            }

            break;
        }

        default:
            break;
    }

    return CP_INFO(cp, cp_index);
}
