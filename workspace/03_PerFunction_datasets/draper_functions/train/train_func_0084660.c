PR_SetFDCacheSize(PRIntn low, PRIntn high)
{


    if (!_pr_initialized) _PR_ImplicitInitialization();

    if (low > high) low = high;

    PR_Lock(_pr_fd_cache.ml);
    if (0 == high)
    {
        if (0 != _pr_fd_cache.limit_high)
        {
            _pr_fd_cache.limit_high = 0;


            while (NULL != _pr_fd_cache.head)
            {
                PRFileDesc *fd = _pr_fd_cache.head;
                _pr_fd_cache.head = fd->higher;
                PR_StackPush(_pr_fd_cache.stack, (PRStackElem*)(&fd->higher));
            }
            _pr_fd_cache.limit_low = 0;
            _pr_fd_cache.tail = NULL;
            _pr_fd_cache.count = 0;
        }
    }
    else
    {
        PRBool was_using_stack = (0 == _pr_fd_cache.limit_high);
        _pr_fd_cache.limit_low = low;
        _pr_fd_cache.limit_high = high;
        if (was_using_stack)
        {
            PRStackElem *pop;
            while (NULL != (pop = PR_StackPop(_pr_fd_cache.stack)))
            {
                PRFileDesc *fd = (PRFileDesc*)
                    ((PRPtrdiff)pop - (PRPtrdiff)stack2fd);
                if (NULL == _pr_fd_cache.tail) _pr_fd_cache.tail = fd;
                fd->higher = _pr_fd_cache.head;
                _pr_fd_cache.head = fd;
                _pr_fd_cache.count += 1;
            }
        }
    }
    PR_Unlock(_pr_fd_cache.ml);
    return PR_SUCCESS;
}
