pipe_block_generic_teardown(void *p, int num_threads)
{
    int retval;
    int join_ret;
    pthread_t *threads = (pthread_t *) p;
    int thread_ret[num_threads];
    void *result;
    int i;

    retval = 0;
    for (i = 0; i < num_threads; ++i) {
        CRUT_DEBUG("waiting for %d...", i);
        join_ret = pthread_join(threads[i], &result);
        if (join_ret) {

            perror("pthread_join");
            retval = join_ret;
        }


        if (result != NULL) {
            thread_ret[i] = *(int *) result;
            free(result);

            CRUT_DEBUG("Thread %d.  return *(%p)=%d.", i, result,
                       thread_ret[i]);

            if (thread_ret[i] < 0) {
                CRUT_FAIL("Thread %d failed (return %d)", i, thread_ret[i]);
                retval = thread_ret[i];
            }

        } else {
            CRUT_FAIL("Thread %d suffered a fatal error (returned NULL)", i);
        }
    }

    if (retval < 0) {
        goto out;
    }


    for (i = 0; i < num_threads; i += 2) {
        if (thread_ret[i] != thread_ret[i + 1]) {
            CRUT_FAIL("Byte transfer mismatch!  Reader reported %d, but writer reported %d",
                 thread_ret[i], thread_ret[i + 1]);
	    retval = -1;
        }
    }

out:
    free(p);

    CRUT_DEBUG("returning %d", retval);
    return retval;
}
