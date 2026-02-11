radeon_mn_unregister(struct radeon_bo *bo)
{
	struct radeon_device *rdev = bo->rdev;
	struct radeon_mn *rmn;
	struct list_head *head;

	mutex_lock(&rdev->mn_lock);
	rmn = bo->mn;
	if (rmn == NULL) {
		mutex_unlock(&rdev->mn_lock);
		return;
	}

	mutex_lock(&rmn->lock);

	head = bo->mn_list.next;

	bo->mn = NULL;
	list_del(&bo->mn_list);

	if (list_empty(head)) {
		struct radeon_mn_node *node;
		node = container_of(head, struct radeon_mn_node, bos);
		interval_tree_remove(&node->it, &rmn->objects);
		kfree(node);
	}

	mutex_unlock(&rmn->lock);
	mutex_unlock(&rdev->mn_lock);
}
