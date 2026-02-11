eq_set_format (int new_channels, int new_rate)
{
    int k;

    pthread_mutex_lock (& mutex);

    channels = new_channels;
    rate = new_rate;


    K = EQ_BANDS;

    while (CF[K - 1] > (float) rate / 2.2)
        K --;


    for (k = 0; k < K; k ++)
        bp2 (a[k], b[k], CF[k] / (float) rate, Q);


    memset (wqv[0][0], 0, sizeof wqv);

    pthread_mutex_unlock (& mutex);
}
