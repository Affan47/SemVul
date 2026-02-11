needs_pd_load_pre(struct intel_engine_cs *engine, struct intel_context *to)
{
	if (!to->ppgtt)
		return false;

	if (engine->last_context == to &&
	    !(intel_engine_flag(engine) & to->ppgtt->pd_dirty_rings))
		return false;

	if (engine->id != RCS)
		return true;

	if (INTEL_INFO(engine->dev)->gen < 8)
		return true;

	return false;
}
