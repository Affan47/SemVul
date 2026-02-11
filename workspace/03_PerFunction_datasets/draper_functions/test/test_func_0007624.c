writesf_free(t_writesf *x)
{

    void *threadrtn;
    pthread_mutex_lock(&x->x_mutex);
    x->x_requestcode = REQUEST_QUIT;

    sfread_cond_signal(&x->x_requestcondition);
    while (x->x_requestcode != REQUEST_NOTHING)
    {

        sfread_cond_signal(&x->x_requestcondition);
        sfread_cond_wait(&x->x_answercondition, &x->x_mutex);
    }
    pthread_mutex_unlock(&x->x_mutex);
    if (pthread_join(x->x_childthread, &threadrtn))
        error("writesf_free: join failed");


    pthread_cond_destroy(&x->x_requestcondition);
    pthread_cond_destroy(&x->x_answercondition);
    pthread_mutex_destroy(&x->x_mutex);
    freebytes(x->x_buf, x->x_bufsize);
}
