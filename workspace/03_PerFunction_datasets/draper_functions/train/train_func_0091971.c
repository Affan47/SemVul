direct_interrupts_to_guc(struct drm_i915_private *dev_priv)
{
	struct intel_engine_cs *engine;
	int irqs;


	irqs = _MASKED_FIELD(GFX_FORWARD_VBLANK_MASK, GFX_FORWARD_VBLANK_ALWAYS);
	irqs |= _MASKED_BIT_ENABLE(GFX_INTERRUPT_STEERING);
	for_each_engine(engine, dev_priv)
		I915_WRITE(RING_MODE_GEN7(engine), irqs);


	irqs = GT_RENDER_USER_INTERRUPT << GEN8_RCS_IRQ_SHIFT |
	       GT_RENDER_USER_INTERRUPT << GEN8_BCS_IRQ_SHIFT;

	I915_WRITE(GUC_BCS_RCS_IER, ~irqs);
	I915_WRITE(GUC_VCS2_VCS1_IER, ~irqs);
	I915_WRITE(GUC_WD_VECS_IER, ~irqs);
}
