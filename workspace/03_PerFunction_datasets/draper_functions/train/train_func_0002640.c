i915_guc_load_status_info(struct seq_file *m, void *data)
{
	struct drm_info_node *node = m->private;
	struct drm_i915_private *dev_priv = node->minor->dev->dev_private;
	struct intel_guc_fw *guc_fw = &dev_priv->guc.guc_fw;
	u32 tmp, i;

	if (!HAS_GUC_UCODE(dev_priv->dev))
		return 0;

	seq_printf(m, "GuC firmware status:\n");
	seq_printf(m, "\tpath: %s\n",
		guc_fw->guc_fw_path);
	seq_printf(m, "\tfetch: %s\n",
		intel_guc_fw_status_repr(guc_fw->guc_fw_fetch_status));
	seq_printf(m, "\tload: %s\n",
		intel_guc_fw_status_repr(guc_fw->guc_fw_load_status));
	seq_printf(m, "\tversion wanted: %d.%d\n",
		guc_fw->guc_fw_major_wanted, guc_fw->guc_fw_minor_wanted);
	seq_printf(m, "\tversion found: %d.%d\n",
		guc_fw->guc_fw_major_found, guc_fw->guc_fw_minor_found);

	tmp = I915_READ(GUC_STATUS);

	seq_printf(m, "\nGuC status 0x%08x:\n", tmp);
	seq_printf(m, "\tBootrom status = 0x%x\n",
		(tmp & GS_BOOTROM_MASK) >> GS_BOOTROM_SHIFT);
	seq_printf(m, "\tuKernel status = 0x%x\n",
		(tmp & GS_UKERNEL_MASK) >> GS_UKERNEL_SHIFT);
	seq_printf(m, "\tMIA Core status = 0x%x\n",
		(tmp & GS_MIA_MASK) >> GS_MIA_SHIFT);
	seq_puts(m, "\nScratch registers:\n");
	for (i = 0; i < 16; i++)
		seq_printf(m, "\t%2d: \t0x%x\n", i, I915_READ(SOFT_SCRATCH(i)));

	return 0;
}
