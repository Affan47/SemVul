lstackGetCount(L_STACK  *lstack)
{
    PROCNAME("lstackGetCount");

    if (!lstack)
        return ERROR_INT("lstack not defined", procName, 1);

    return lstack->n;
}
