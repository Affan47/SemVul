fpixaChangeRefcount(FPIXA   *fpixa,
                    l_int32  delta)
{
    PROCNAME("fpixaChangeRefcount");

    if (!fpixa)
        return ERROR_INT("fpixa not defined", procName, 1);

    fpixa->refcount += delta;
    return 0;
}
