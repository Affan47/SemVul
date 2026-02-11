env_memsize(const void *ptr)
{
    if (ptr) {
	const rb_env_t * const env = ptr;
	size_t size = sizeof(rb_env_t);
	if (env->env) {
	    size += env->env_size * sizeof(VALUE);
	}
	return size;
    }
    return 0;
}
