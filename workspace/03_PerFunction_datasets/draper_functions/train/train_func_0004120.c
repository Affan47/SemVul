i915_gem_reset_engine_cleanup(struct drm_i915_private *dev_priv,
					struct intel_engine_cs *engine)
{
	struct intel_ringbuffer *buffer;

	while (!list_empty(&engine->active_list)) {
		struct drm_i915_gem_object *obj;

		obj = list_first_entry(&engine->active_list,
				       struct drm_i915_gem_object,
				       engine_list[engine->id]);

		i915_gem_object_retire__read(obj, engine->id);
	}


	if (i915.enable_execlists) {

		tasklet_kill(&engine->irq_tasklet);

		spin_lock_bh(&engine->execlist_lock);

		list_splice_tail_init(&engine->execlist_queue,
				      &engine->execlist_retired_req_list);
		spin_unlock_bh(&engine->execlist_lock);

		intel_execlists_retire_requests(engine);
	}


	while (!list_empty(&engine->request_list)) {
		struct drm_i915_gem_request *request;

		request = list_first_entry(&engine->request_list,
					   struct drm_i915_gem_request,
					   list);

		i915_gem_request_retire(request);
	}


	list_for_each_entry(buffer, &engine->buffers, link) {
		buffer->last_retired_head = buffer->tail;
		intel_ring_update_space(buffer);
	}

	intel_ring_init_seqno(engine, engine->last_submitted_seqno);
}
