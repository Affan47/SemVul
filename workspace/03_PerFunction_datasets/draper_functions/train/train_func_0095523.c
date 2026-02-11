kgd2kfd_interrupt(struct kfd_dev *kfd, const void *ih_ring_entry)
{
	if (!kfd->init_complete)
		return;

	spin_lock(&kfd->interrupt_lock);

	if (kfd->interrupts_active
	    && interrupt_is_wanted(kfd, ih_ring_entry)
	    && enqueue_ih_ring_entry(kfd, ih_ring_entry))
		schedule_work(&kfd->interrupt_work);

	spin_unlock(&kfd->interrupt_lock);
}
