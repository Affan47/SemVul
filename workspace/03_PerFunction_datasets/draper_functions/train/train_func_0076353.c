i915_drpc_info(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = m->private;
	struct drm_device *dev = node->minor->dev;

	if (IS_VALLEYVIEW(dev) || IS_CHERRYVIEW(dev))
		return vlv_drpc_info(m);
	else if (INTEL_INFO(dev)->gen >= 6)
		return gen6_drpc_info(m);
	else
		return ironlake_drpc_info(m);
}
