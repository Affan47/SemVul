Csemaphore_down (CSemaphore * s)
{
    int         value_after_op;

    tw_pthread_mutex_lock ((void *)(s));
    while (s->v <= 0)
    {
     tw_pthread_cond_wait ((void *)(s));
    }

    (s->v)--;
    value_after_op = s->v;

    tw_pthread_mutex_unlock ((void *)(s));

    return (value_after_op);
}
