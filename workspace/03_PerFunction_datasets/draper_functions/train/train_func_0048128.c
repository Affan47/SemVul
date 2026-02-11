ntb_create_thread(void *(* thread_func)(void *),
                  void *user_data)
{
        pthread_t thread;
        int result;

        result = pthread_create(&thread,
                                NULL,
                                thread_func,
                                user_data);

        if (result)
                ntb_fatal("Error creating thread: %s",
                          strerror(result));

        return thread;
}
