vc4_hvs_debugfs_regs(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	struct drm_device *dev = node->minor->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	int i;

	for (i = 0; i < ARRAY_SIZE(hvs_regs); i++) {
		seq_printf(m, "%s (0x%04x): 0x%08x\n",
			   hvs_regs[i].name, hvs_regs[i].reg,
			   HVS_READ(hvs_regs[i].reg));
	}

	return 0;
}
