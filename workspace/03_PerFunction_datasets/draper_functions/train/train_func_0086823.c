i915_gem_context_free(struct kref *ctx_ref)
{
	struct intel_context *ctx = container_of(ctx_ref, typeof(*ctx), ref);

	trace_i915_context_free(ctx);

	if (i915.enable_execlists)
		intel_lr_context_free(ctx);


	i915_gem_context_clean(ctx);

	i915_ppgtt_put(ctx->ppgtt);

	if (ctx->legacy_hw_ctx.rcs_state)
		drm_gem_object_unreference(&ctx->legacy_hw_ctx.rcs_state->base);
	list_del(&ctx->link);
	kfree(ctx);
}
