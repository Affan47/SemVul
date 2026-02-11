PR_EnumerateThreads(PREnumerator func, void *arg)
{
    PRIntn count = 0;
    PRStatus rv = PR_SUCCESS;
    PRThread* thred = pt_book.first;

#if defined(DEBUG) || defined(FORCE_PR_ASSERT)
#if !defined(_PR_DCETHREADS)
    PRThread *me = PR_GetCurrentThread();
#endif
#endif

    PR_LOG(_pr_gc_lm, PR_LOG_ALWAYS, ("Begin PR_EnumerateThreads\n"));


    PR_ASSERT(suspendAllOn);

    while (thred != NULL)
    {


        PRThread* next = thred->next;

        if (_PT_IS_GCABLE_THREAD(thred))
        {
#if !defined(_PR_DCETHREADS)
            PR_ASSERT((thred == me) || (thred->suspend & PT_THREAD_SUSPENDED));
#endif
            PR_LOG(_pr_gc_lm, PR_LOG_ALWAYS,
                   ("In PR_EnumerateThreads callback thread %p thid = %X\n",
                    thred, thred->id));

            rv = func(thred, count++, arg);
            if (rv != PR_SUCCESS)
                return rv;
        }
        thred = next;
    }
    PR_LOG(_pr_gc_lm, PR_LOG_ALWAYS,
	   ("End PR_EnumerateThreads count = %d \n", count));
    return rv;
}
