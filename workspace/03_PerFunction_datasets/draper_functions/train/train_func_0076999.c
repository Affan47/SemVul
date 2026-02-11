listAssemblyexceptionCompareReferenceEndDescending(
    const void *item1,
    const void *item2)
{
    int result = 0;

    EnsPAssemblyexception ae1 = *(EnsOAssemblyexception *const *) item1;
    EnsPAssemblyexception ae2 = *(EnsOAssemblyexception *const *) item2;

#if defined(AJ_DEBUG) && AJ_DEBUG >= 2
    if (ajDebugTest("listAssemblyexceptionCompareReferenceEndDescending"))
    {
        ajDebug("listAssemblyexceptionCompareReferenceEndDescending\n"
                "  ae1 %p\n"
                "  ae2 %p\n",
                ae1,
                ae2);

        ensAssemblyexceptionTrace(ae1, 1);
        ensAssemblyexceptionTrace(ae2, 1);
    }
#endif


    if (ae1 && (!ae2))
        return -1;

    if ((!ae1) && (!ae2))
        return 0;

    if ((!ae1) && ae2)
        return +1;

    if (ae1->ReferenceEnd < ae2->ReferenceEnd)
        result = +1;

    if (ae1->ReferenceEnd > ae2->ReferenceEnd)
        result = -1;

    return result;
}
