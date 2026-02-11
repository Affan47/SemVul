Wait() {
    int err;
    if ((err = pthread_cond_wait(&cond, &mutex)) != 0)
        Severe("Error from pthread_cond_wait: %s", strerror(err));
}
