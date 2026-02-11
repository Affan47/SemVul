avail_signal(avail_t *ap)
{
    pthread_mutex_lock(&ap->mtx);
    if (ap->avail)
	pthread_mutex_unlock(&ap->mtx);
    else
    {
	ap->avail = 1;
	pthread_mutex_unlock(&ap->mtx);
	pthread_cond_broadcast(&ap->cv);
    }

    return 0;
}
