sarrayCopy(SARRAY  *sa)
{
l_int32  i;
SARRAY  *csa;

    PROCNAME("sarrayCopy");

    if (!sa)
        return (SARRAY *)ERROR_PTR("sa not defined", procName, NULL);

    if ((csa = sarrayCreate(sa->nalloc)) == NULL)
        return (SARRAY *)ERROR_PTR("csa not made", procName, NULL);

    for (i = 0; i < sa->n; i++)
        sarrayAddString(csa, sa->array[i], L_COPY);

    return csa;
}
