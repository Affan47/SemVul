SetProcessorAffinityOfCurrentThread(unsigned int cpunum)
{
    Thread::Init();

    Thread* thread = Thread::CurrentThread();
    if (thread)
    {
        return thread->setProcessorAffinity(cpunum);
    }
    else
    {
#if defined(HAVE_PTHREAD_SETAFFINITY_NP) || defined(HAVE_THREE_PARAM_SCHED_SETAFFINITY) || defined(HAVE_TWO_PARAM_SCHED_SETAFFINITY)
        cpu_set_t cpumask;
        CPU_ZERO( &cpumask );
        CPU_SET( cpunum, &cpumask );
#if defined(HAVE_PTHREAD_SETAFFINITY_NP)
        pthread_setaffinity_np( pthread_self(), sizeof(cpumask), &cpumask);
        return 0;
#elif defined(HAVE_THREE_PARAM_SCHED_SETAFFINITY)
        sched_setaffinity( 0, sizeof(cpumask), &cpumask );
        return 0;
#elif defined(HAVE_TWO_PARAM_SCHED_SETAFFINITY)
        sched_setaffinity( 0, &cpumask );
        return 0;
#endif
#endif
    }

    return -1;
}
