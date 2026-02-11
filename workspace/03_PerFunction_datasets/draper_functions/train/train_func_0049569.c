PR_NewThreadPrivateIndex(
    PRUintn *newIndex, PRThreadPrivateDTOR dtor)
{
    PRStatus rv;
    PRInt32 index;

    if (!_pr_initialized) _PR_ImplicitInitialization();

    PR_ASSERT(NULL != newIndex);
    PR_ASSERT(NULL != _pr_tpd_destructors);

    index = PR_ATOMIC_INCREMENT(&_pr_tpd_highwater) - 1;
    if (_PR_TPD_LIMIT <= index)
    {
        PR_SetError(PR_TPD_RANGE_ERROR, 0);
        rv = PR_FAILURE;
    }
    else
    {
        _pr_tpd_destructors[index] = dtor;
        *newIndex = (PRUintn)index;
        rv = PR_SUCCESS;
    }

    return rv;
}
