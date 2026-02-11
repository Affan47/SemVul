ring_full(ring_buffer_t *ring)
{
    int status, full;


    status = pthread_mutex_lock(&ring->mutex);
    if (status != 0)
        error("Could not get access to ring buffer mutex");

    full = !ring->space_ready;


    status = pthread_mutex_unlock(&ring->mutex);
    if (status != 0)
        error("Could not relinquish access to ring buffer mutex");


    return full;
}
