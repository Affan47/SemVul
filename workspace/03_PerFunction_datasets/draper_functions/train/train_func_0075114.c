free ( Job* job )
{
    QMutexLocker l ( & d->mutex );
    int position = d->customers.indexOf (job);

    if (position != -1)
    {
        debug ( 4, "ResourceRestrictionPolicy::free: job %p done.\n", (void*)job );
        d->customers.removeAt (position);
    }
}
