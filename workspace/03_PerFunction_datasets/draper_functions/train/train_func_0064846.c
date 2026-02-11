unsafeDefineClass(Class *clazz, MethodBlock *mb,
                                   uintptr_t *ostack) {
    Object *string   = (Object *)ostack[1];
    Object *array    = (Object *)ostack[2];
    int32_t offset   = ostack[3];
    int32_t data_len = ostack[4];
    Class *class     = NULL;

    TRACE("unsafeDefineClass\n");

    if(array == NULL)
        signalException(java_lang_NullPointerException, NULL);
    else
        if((offset < 0) || (data_len < 0) ||
                           ((offset + data_len) > ARRAY_LEN(array)))
            signalException(java_lang_ArrayIndexOutOfBoundsException, NULL);
        else {
            char *data = ARRAY_DATA(array, char);
            char *name = string ? dots2Slash(String2Utf8(string)) : NULL;

            class = defineClass(name, data, offset, data_len, NULL);
            sysFree(name);

            if(class != NULL)
                linkClass(class);
        }

    *ostack++ = (uintptr_t) class;
    return ostack;
}
