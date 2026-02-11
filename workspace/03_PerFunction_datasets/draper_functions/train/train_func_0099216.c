i915_error_state_free(struct kref *error_ref)
{
	struct drm_i915_error_state *error = container_of(error_ref,
							  typeof(*error), ref);
	int i;

	for (i = 0; i < ARRAY_SIZE(error->ring); i++) {
		i915_error_object_free(error->ring[i].batchbuffer);
		i915_error_object_free(error->ring[i].wa_batchbuffer);
		i915_error_object_free(error->ring[i].ringbuffer);
		i915_error_object_free(error->ring[i].hws_page);
		i915_error_object_free(error->ring[i].ctx);
		kfree(error->ring[i].requests);
		i915_error_object_free(error->ring[i].wa_ctx);
	}

	i915_error_object_free(error->semaphore_obj);

	for (i = 0; i < error->vm_count; i++)
		kfree(error->active_bo[i]);

	kfree(error->active_bo);
	kfree(error->active_bo_count);
	kfree(error->pinned_bo);
	kfree(error->pinned_bo_count);
	kfree(error->overlay);
	kfree(error->display);
	kfree(error);
}
