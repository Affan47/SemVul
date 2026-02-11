__B(Class *class, MethodBlock *mb, uintptr_t *ostack) {
    if(!initJNILrefs())
        return NULL;

    *ostack = (*(int8_t (*)(void*, void*))mb->code) (
	&jni_env,
	(void*)ostack[0]);

    return ostack + 1;
}
