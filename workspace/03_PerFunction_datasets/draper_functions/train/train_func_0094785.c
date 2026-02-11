kfd_ioctl_destroy_queue(struct file *filp, struct kfd_process *p,
					void *data)
{
	int retval;
	struct kfd_ioctl_destroy_queue_args *args = data;

	pr_debug("kfd: destroying queue id %d for PASID %d\n",
				args->queue_id,
				p->pasid);

	mutex_lock(&p->mutex);

	retval = pqm_destroy_queue(&p->pqm, args->queue_id);

	mutex_unlock(&p->mutex);
	return retval;
}
