subunits_stuck(struct intel_engine_cs *engine)
{
	u32 instdone[I915_NUM_INSTDONE_REG];
	bool stuck;
	int i;

	if (engine->id != RCS)
		return true;

	i915_get_extra_instdone(engine->dev, instdone);


	stuck = true;
	for (i = 0; i < I915_NUM_INSTDONE_REG; i++) {
		const u32 tmp = instdone[i] | engine->hangcheck.instdone[i];

		if (tmp != engine->hangcheck.instdone[i])
			stuck = false;

		engine->hangcheck.instdone[i] |= tmp;
	}

	return stuck;
}
