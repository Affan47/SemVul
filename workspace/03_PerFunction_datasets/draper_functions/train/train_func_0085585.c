vfio_virqfd_disable(struct virqfd **pvirqfd)
{
	unsigned long flags;

	spin_lock_irqsave(&virqfd_lock, flags);

	if (*pvirqfd) {
		virqfd_deactivate(*pvirqfd);
		*pvirqfd = NULL;
	}

	spin_unlock_irqrestore(&virqfd_lock, flags);


	flush_workqueue(vfio_irqfd_cleanup_wq);
}
