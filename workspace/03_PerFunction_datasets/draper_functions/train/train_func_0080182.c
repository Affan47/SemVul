SortImperfectCRLs(const void* arg1, const void* arg2)
{
    CachedCrl* a, *b;

    a = *(CachedCrl**) arg1;
    b = *(CachedCrl**) arg2;

    if (!a || !b)
    {
        PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
        PORT_Assert(0);
    }
    else
    {
        PRBool aDecoded = PR_FALSE, bDecoded = PR_FALSE;
        if ( (PR_TRUE == a->sigValid) && (PR_TRUE == b->sigValid) )
        {

            return SortCRLsByThisUpdate(arg1, arg2);
        }
        if (PR_TRUE == a->sigValid)
        {
            return 1;
        }
        if (PR_TRUE == b->sigValid)
        {
            return -1;
        }
        aDecoded = GetOpaqueCRLFields(a->crl)->decodingError;
        bDecoded = GetOpaqueCRLFields(b->crl)->decodingError;

        if ( (PR_FALSE == aDecoded) && (PR_FALSE == bDecoded) )
        {

            return SortCRLsByThisUpdate(arg1, arg2);
        }
        if (PR_FALSE == aDecoded)
        {
            return 1;
        }
        if (PR_FALSE == bDecoded)
        {
            return -1;
        }

    }

    PORT_Assert(a != b);
    return a>b?1:-1;
}
