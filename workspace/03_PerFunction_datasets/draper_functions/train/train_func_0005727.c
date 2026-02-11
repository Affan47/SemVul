trace_pointer_real(const char *name, const void *vptrptr)
{
    const void *ptr;
    const void *const *ptr_ptr = (const void *const *)vptrptr;

    ptr = *ptr_ptr;
    if (!ptr)
	trace_printf("%s = NULL;\n", name);
    else
	trace_printf("%s = 0x%08lX;\n", name, (long)ptr);
}
