i915_irq_uninstall(struct drm_device * dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int pipe;

	if (I915_HAS_HOTPLUG(dev)) {
		i915_hotplug_interrupt_update(dev_priv, 0xffffffff, 0);
		I915_WRITE(PORT_HOTPLUG_STAT, I915_READ(PORT_HOTPLUG_STAT));
	}

	I915_WRITE16(HWSTAM, 0xffff);
	for_each_pipe(dev_priv, pipe) {

		I915_WRITE(PIPESTAT(pipe), 0);
		I915_WRITE(PIPESTAT(pipe), I915_READ(PIPESTAT(pipe)));
	}
	I915_WRITE(IMR, 0xffffffff);
	I915_WRITE(IER, 0x0);

	I915_WRITE(IIR, I915_READ(IIR));
}
