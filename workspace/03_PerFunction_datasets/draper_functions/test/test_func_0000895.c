notify_ring(struct intel_engine_cs *engine)
{
	if (!intel_engine_initialized(engine))
		return;

	trace_i915_gem_request_notify(engine);
	engine->user_interrupts++;

	wake_up_all(&engine->irq_queue);
}
