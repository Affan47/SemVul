ring_pop(ring_buffer_t *ring)
{
    int status;


    status = pthread_mutex_lock(&ring->mutex);
    if (status != 0)
	error("Could not get access to ring buffer mutex");


    while (ring->data_ready == 0) {
	status = pthread_cond_wait(&ring->data_ready_cond, &ring->mutex);
	if (status != 0)
    	    error("Could not wait for ring buffer to accumulate data");
    }


    ring->base_data = (ring->base_data + 1) % MAX_BLOCKS_QUEUED;
    if (--(ring->count_data) == 0)
	ring->data_ready = 0;


    ring->space_ready = 1;
    status = pthread_cond_signal(&ring->space_ready_cond);
    if (status != 0)
	error("Could not signal space-ready condition");


    status = pthread_mutex_unlock(&ring->mutex);
    if (status != 0)
	error("Could not relinquish access to ring buffer mutex");


    return 0;
}
