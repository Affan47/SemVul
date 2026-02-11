ntb_pow_free(struct ntb_pow *pow)
{
        struct ntb_pow_cookie *cookie, *tmp;
        int i;

        pthread_mutex_lock(&pow->mutex);
        pow->quit = true;
        pthread_cond_broadcast(&pow->cond);
        pthread_mutex_unlock(&pow->mutex);

        for (i = 0; i < pow->n_threads; i++)
                pthread_join(pow->threads[i], NULL);

        ntb_list_for_each_safe(cookie, tmp, &pow->queue, link)
                remove_queued_cookie(cookie);

        pthread_mutex_destroy(&pow->mutex);
        pthread_cond_destroy(&pow->cond);

        ntb_free(pow->threads);
        ntb_free(pow);
}
