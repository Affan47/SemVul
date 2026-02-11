lstackAdd(L_STACK  *lstack,
          void     *item)
{
    PROCNAME("lstackAdd");

    if (!lstack)
        return ERROR_INT("lstack not defined", procName, 1);
    if (!item)
        return ERROR_INT("item not defined", procName, 1);


    if (lstack->n >= lstack->nalloc)
        lstackExtendArray(lstack);


    lstack->array[lstack->n] = (void *)item;
    lstack->n++;

    return 0;
}
