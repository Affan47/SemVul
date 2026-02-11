guc_add_workqueue_item(struct i915_guc_client *gc,
				  struct drm_i915_gem_request *rq)
{
	enum intel_ring_id ring_id = rq->ring->id;
	struct guc_wq_item *wqi;
	void *base;
	u32 tail, wq_len, wq_off = 0;
	int ret;

	ret = guc_get_workqueue_space(gc, &wq_off);
	if (ret)
		return ret;


	WARN_ON(sizeof(struct guc_wq_item) != 16);
	WARN_ON(wq_off & 3);


	base = kmap_atomic(i915_gem_object_get_page(gc->client_obj,
			(wq_off + GUC_DB_SIZE) >> PAGE_SHIFT));
	wq_off &= PAGE_SIZE - 1;
	wqi = (struct guc_wq_item *)((char *)base + wq_off);


	wq_len = sizeof(struct guc_wq_item) / sizeof(u32) - 1;
	wqi->header = WQ_TYPE_INORDER |
			(wq_len << WQ_LEN_SHIFT) |
			(ring_id << WQ_TARGET_SHIFT) |
			WQ_NO_WCFLUSH_WAIT;


	wqi->context_desc = (u32)intel_lr_context_descriptor(rq->ctx, rq->ring);


	tail = rq->ringbuf->tail >> 3;
	wqi->ring_tail = tail << WQ_RING_TAIL_SHIFT;
	wqi->fence_id = 0;

	kunmap_atomic(base);

	return 0;
}
