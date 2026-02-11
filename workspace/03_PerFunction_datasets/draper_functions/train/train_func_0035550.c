intel_logical_ring_advance_and_submit(struct drm_i915_gem_request *request)
{
	struct intel_ringbuffer *ringbuf = request->ringbuf;
	struct drm_i915_private *dev_priv = request->i915;
	struct intel_engine_cs *engine = request->engine;

	intel_logical_ring_advance(ringbuf);
	request->tail = ringbuf->tail;


	intel_logical_ring_emit(ringbuf, MI_NOOP);
	intel_logical_ring_emit(ringbuf, MI_NOOP);
	intel_logical_ring_advance(ringbuf);

	if (intel_engine_stopped(engine))
		return 0;

	if (engine->last_context != request->ctx) {
		if (engine->last_context)
			intel_lr_context_unpin(engine->last_context, engine);
		if (request->ctx != request->i915->kernel_context) {
			intel_lr_context_pin(request->ctx, engine);
			engine->last_context = request->ctx;
		} else {
			engine->last_context = NULL;
		}
	}

	if (dev_priv->guc.execbuf_client)
		i915_guc_submit(dev_priv->guc.execbuf_client, request);
	else
		execlists_context_queue(request);

	return 0;
}
