logical_ring_init(struct drm_device *dev, struct intel_engine_cs *ring)
{
	int ret;


	ring->buffer = NULL;

	ring->dev = dev;
	INIT_LIST_HEAD(&ring->active_list);
	INIT_LIST_HEAD(&ring->request_list);
	i915_gem_batch_pool_init(dev, &ring->batch_pool);
	init_waitqueue_head(&ring->irq_queue);

	INIT_LIST_HEAD(&ring->execlist_queue);
	INIT_LIST_HEAD(&ring->execlist_retired_req_list);
	spin_lock_init(&ring->execlist_lock);

	ret = i915_cmd_parser_init_ring(ring);
	if (ret)
		return ret;

	ret = intel_lr_context_deferred_alloc(ring->default_context, ring);
	if (ret)
		return ret;


	ret = intel_lr_context_do_pin(
			ring,
			ring->default_context->engine[ring->id].state,
			ring->default_context->engine[ring->id].ringbuf);
	if (ret) {
		DRM_ERROR(
			"Failed to pin and map ringbuffer %s: %d\n",
			ring->name, ret);
		return ret;
	}

	return ret;
}
