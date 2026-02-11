interface_show_error (const char * message)
{
    pthread_mutex_lock (& error_mutex);

    g_queue_push_tail (& error_queue, g_strdup (message));

    if (! error_source)
        error_source = g_idle_add (error_idle_func, NULL);

    pthread_mutex_unlock (& error_mutex);
}
