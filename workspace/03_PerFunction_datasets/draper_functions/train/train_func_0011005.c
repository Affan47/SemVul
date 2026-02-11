fn_free_functions(const gs_function_t *const * Functions, int count,
                  gs_memory_t * mem)
{
    int i;

    for (i = count; --i >= 0;)
        if (Functions[i])
            gs_function_free((gs_function_t *)Functions[i], true, mem);
    gs_free_const_object(mem, Functions, "Functions");
}
