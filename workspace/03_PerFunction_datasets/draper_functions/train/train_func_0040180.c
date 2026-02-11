i915_gem_request_alloc(struct intel_engine_cs *engine,
		       struct intel_context *ctx)
{
	struct drm_i915_gem_request *req;
	int err;

	if (ctx == NULL)
		ctx = to_i915(engine->dev)->kernel_context;
	err = __i915_gem_request_alloc(engine, ctx, &req);
	return err ? ERR_PTR(err) : req;
}
