pqm_destroy_queue(struct process_queue_manager *pqm, unsigned int qid)
{
	struct process_queue_node *pqn;
	struct kfd_process_device *pdd;
	struct device_queue_manager *dqm;
	struct kfd_dev *dev;
	int retval;

	dqm = NULL;

	BUG_ON(!pqm);
	retval = 0;

	pr_debug("kfd: In Func %s\n", __func__);

	pqn = get_queue_by_qid(pqm, qid);
	if (pqn == NULL) {
		pr_err("kfd: queue id does not match any known queue\n");
		return -EINVAL;
	}

	dev = NULL;
	if (pqn->kq)
		dev = pqn->kq->dev;
	if (pqn->q)
		dev = pqn->q->device;
	BUG_ON(!dev);

	pdd = kfd_get_process_device_data(dev, pqm->process);
	if (!pdd) {
		pr_err("Process device data doesn't exist\n");
		return -1;
	}

	if (pqn->kq) {

		dqm = pqn->kq->dev->dqm;
		dqm->ops.destroy_kernel_queue(dqm, pqn->kq, &pdd->qpd);
		kernel_queue_uninit(pqn->kq);
	}

	if (pqn->q) {
		dqm = pqn->q->device->dqm;
		retval = dqm->ops.destroy_queue(dqm, &pdd->qpd, pqn->q);
		if (retval != 0)
			return retval;

		uninit_queue(pqn->q);
	}

	list_del(&pqn->process_queue_list);
	kfree(pqn);
	clear_bit(qid, pqm->queue_slot_bitmap);

	if (list_empty(&pqm->queues))
		dqm->ops.unregister_process(dqm, &pdd->qpd);

	return retval;
}
