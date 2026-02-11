qxl_debugfs_buffers_info(struct seq_file *m, void *data)
{
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct qxl_device *qdev = node->minor->dev->dev_private;
	struct qxl_bo *bo;

	list_for_each_entry(bo, &qdev->gem.objects, list) {
		struct reservation_object_list *fobj;
		int rel;

		rcu_read_lock();
		fobj = rcu_dereference(bo->tbo.resv->fence);
		rel = fobj ? fobj->shared_count : 0;
		rcu_read_unlock();

		seq_printf(m, "size %ld, pc %d, num releases %d\n",
			   (unsigned long)bo->gem_base.size,
			   bo->pin_count, rel);
	}
	return 0;
}
