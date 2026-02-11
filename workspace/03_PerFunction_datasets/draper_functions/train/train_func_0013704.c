static_DD_D(Class *class, MethodBlock *mb, uintptr_t *ostack) {
    if(!initJNILrefs())
        return NULL;

    *(double*)ostack = (*(double (*)(void*, void*, double, double))mb->code) (
	&jni_env,
	class,
	*(double *)&ostack[0],
	*(double *)&ostack[2]);

    return ostack + 2;
}
