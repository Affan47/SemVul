ring_buffer_put_async(struct ring_buffer *rb)
{
	if (!atomic_dec_and_test(&rb->refcount))
		return;

	rb->rcu_head.next = (void *)rb;
	irq_work_queue(&rb->irq_work);
}
