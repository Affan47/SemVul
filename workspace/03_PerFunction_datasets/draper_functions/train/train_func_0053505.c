MW_ExpandHashInternal(PRWaitGroup *group)
{
    PRRecvWait **desc;
    PRUint32 pidx, length;
    _PRWaiterHash *newHash, *oldHash = group->waiter;
    PRBool retry;
    _PR_HashStory hrv;

    static const PRInt32 prime_number[] = {
        _PR_DEFAULT_HASH_LENGTH, 179, 521, 907, 1427,
        2711, 3917, 5021, 8219, 11549, 18911, 26711, 33749, 44771};
    PRUintn primes = (sizeof(prime_number) / sizeof(PRInt32));


    for (pidx = 0; pidx < primes; ++pidx)
    {
        if (prime_number[pidx] == oldHash->length)
        {
            break;
        }
    }

    PR_ASSERT(pidx < primes);


    while (pidx < primes - 1)
    {

        ++pidx;
        length = prime_number[pidx];


        newHash = (_PRWaiterHash*)PR_CALLOC(
            sizeof(_PRWaiterHash) + (length * sizeof(PRRecvWait*)));
        if (NULL == newHash)
        {
            PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
            return _prmw_error;
        }

        newHash->length = length;
        retry = PR_FALSE;
        for (desc = &oldHash->recv_wait;
            newHash->count < oldHash->count; ++desc)
        {
            PR_ASSERT(desc < &oldHash->recv_wait + oldHash->length);
            if (NULL != *desc)
            {
                hrv = MW_AddHashInternal(*desc, newHash);
                PR_ASSERT(_prmw_error != hrv);
                if (_prmw_success != hrv)
                {
                    PR_DELETE(newHash);
                    retry = PR_TRUE;
                    break;
                }
            }
        }
        if (retry) continue;

        PR_DELETE(group->waiter);
        group->waiter = newHash;
        group->p_timestamp += 1;
        return _prmw_success;
    }

    PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
    return _prmw_error;
}
