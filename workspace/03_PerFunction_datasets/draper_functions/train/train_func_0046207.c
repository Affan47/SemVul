kfd_ioctl_create_queue(struct file *filep, struct kfd_process *p,
					void *data)
{
	struct kfd_ioctl_create_queue_args *args = data;
	struct kfd_dev *dev;
	int err = 0;
	unsigned int queue_id;
	struct kfd_process_device *pdd;
	struct queue_properties q_properties;

	memset(&q_properties, 0, sizeof(struct queue_properties));

	pr_debug("kfd: creating queue ioctl\n");

	err = set_queue_properties_from_user(&q_properties, args);
	if (err)
		return err;

	pr_debug("kfd: looking for gpu id 0x%x\n", args->gpu_id);
	dev = kfd_device_by_id(args->gpu_id);
	if (dev == NULL) {
		pr_debug("kfd: gpu id 0x%x was not found\n", args->gpu_id);
		return -EINVAL;
	}

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	if (IS_ERR(pdd)) {
		err = -ESRCH;
		goto err_bind_process;
	}

	pr_debug("kfd: creating queue for PASID %d on GPU 0x%x\n",
			p->pasid,
			dev->id);

	err = pqm_create_queue(&p->pqm, dev, filep, &q_properties,
				0, q_properties.type, &queue_id);
	if (err != 0)
		goto err_create_queue;

	args->queue_id = queue_id;


	args->doorbell_offset = (KFD_MMAP_DOORBELL_MASK | args->gpu_id);
	args->doorbell_offset <<= PAGE_SHIFT;

	mutex_unlock(&p->mutex);

	pr_debug("kfd: queue id %d was created successfully\n", args->queue_id);

	pr_debug("ring buffer address == 0x%016llX\n",
			args->ring_base_address);

	pr_debug("read ptr address    == 0x%016llX\n",
			args->read_pointer_address);

	pr_debug("write ptr address   == 0x%016llX\n",
			args->write_pointer_address);

	return 0;

err_create_queue:
err_bind_process:
	mutex_unlock(&p->mutex);
	return err;
}
