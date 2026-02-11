nvme_kill_queues(struct nvme_ctrl *ctrl)
{
	struct nvme_ns *ns;

	mutex_lock(&ctrl->namespaces_mutex);
	list_for_each_entry(ns, &ctrl->namespaces, list) {
		if (!kref_get_unless_zero(&ns->kref))
			continue;


		if (!test_and_set_bit(NVME_NS_DEAD, &ns->flags))
			revalidate_disk(ns->disk);

		blk_set_queue_dying(ns->queue);
		blk_mq_abort_requeue_list(ns->queue);
		blk_mq_start_stopped_hw_queues(ns->queue, true);

		nvme_put_ns(ns);
	}
	mutex_unlock(&ctrl->namespaces_mutex);
}
