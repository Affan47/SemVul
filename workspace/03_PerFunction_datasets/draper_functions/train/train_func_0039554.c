i915_wa_registers(struct seq_file *m, void *unused)
{
	int i;
	int ret;
	struct intel_engine_cs *engine;
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct drm_device *dev = node->minor->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_workarounds *workarounds = &dev_priv->workarounds;
	enum intel_engine_id id;

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		return ret;

	intel_runtime_pm_get(dev_priv);

	seq_printf(m, "Workarounds applied: %d\n", workarounds->count);
	for_each_engine_id(engine, dev_priv, id)
		seq_printf(m, "HW whitelist count for %s: %d\n",
			   engine->name, workarounds->hw_whitelist_count[id]);
	for (i = 0; i < workarounds->count; ++i) {
		i915_reg_t addr;
		u32 mask, value, read;
		bool ok;

		addr = workarounds->reg[i].addr;
		mask = workarounds->reg[i].mask;
		value = workarounds->reg[i].value;
		read = I915_READ(addr);
		ok = (value & mask) == (read & mask);
		seq_printf(m, "0x%X: 0x%08X, mask: 0x%08X, read: 0x%08x, status: %s\n",
			   i915_mmio_reg_offset(addr), value, mask, read, ok ? "OK" : "FAIL");
	}

	intel_runtime_pm_put(dev_priv);
	mutex_unlock(&dev->struct_mutex);

	return 0;
}
