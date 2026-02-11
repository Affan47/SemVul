DXFree(Pointer x)
{
    if (!x)
	return OK;

    if (FOUND(x))
	DXFoundAlloc();
    if (trace && !DXTraceAlloc(trace))
	return ERROR;

    if (SMALL(x))
	return afree(small, x);

    else if (LARGE(x))
	return afree(large, x);

    else
#if (!MALLOC_NONE && !MALLOC_GLOBAL) || MALLOC_LOCAL
	free(x);
#else
        return ERROR;
#endif

    return OK;
}
