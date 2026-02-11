acquire_packet_buffer(struct kernel_queue *kq,
		size_t packet_size_in_dwords, unsigned int **buffer_ptr)
{
	size_t available_size;
	size_t queue_size_dwords;
	uint32_t wptr, rptr;
	unsigned int *queue_address;

	BUG_ON(!kq || !buffer_ptr);

	rptr = *kq->rptr_kernel;
	wptr = *kq->wptr_kernel;
	queue_address = (unsigned int *)kq->pq_kernel_addr;
	queue_size_dwords = kq->queue->properties.queue_size / sizeof(uint32_t);

	pr_debug("rptr: %d\n", rptr);
	pr_debug("wptr: %d\n", wptr);
	pr_debug("queue_address 0x%p\n", queue_address);

	available_size = (rptr - 1 - wptr + queue_size_dwords) %
							queue_size_dwords;

	if (packet_size_in_dwords >= queue_size_dwords ||
			packet_size_in_dwords >= available_size) {


		*buffer_ptr = NULL;
		return -ENOMEM;
	}

	if (wptr + packet_size_in_dwords >= queue_size_dwords) {
		while (wptr > 0) {
			queue_address[wptr] = kq->nop_packet;
			wptr = (wptr + 1) % queue_size_dwords;
		}
	}

	*buffer_ptr = &queue_address[wptr];
	kq->pending_wptr = wptr + packet_size_in_dwords;

	return 0;
}
