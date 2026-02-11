static_IIII_I(Class *class, MethodBlock *mb, uintptr_t *ostack) {
    if(!initJNILrefs())
        return NULL;

    *ostack = (*(uintptr_t (*)(void*, void*, uintptr_t, uintptr_t, uintptr_t, uintptr_t))mb->code) (
	&jni_env,
	class,
	*(uintptr_t *)&ostack[0],
	*(uintptr_t *)&ostack[1],
	*(uintptr_t *)&ostack[2],
	*(uintptr_t *)&ostack[3]);

    return ostack + 1;
}
