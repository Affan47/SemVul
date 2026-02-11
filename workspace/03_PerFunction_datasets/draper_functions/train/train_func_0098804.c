trace_pointer_real(char *name, void *vptrptr)
{
    void            **ptr_ptr = vptrptr;
    void            *ptr;

    ptr = *ptr_ptr;
    if (!ptr)
        trace_printf("%s = NULL;\n", name);
    else
        trace_printf("%s = 0x%08lX;\n", name, (long)ptr);
}
