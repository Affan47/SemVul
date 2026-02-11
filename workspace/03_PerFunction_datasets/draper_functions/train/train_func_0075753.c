i915_dp_mst_info(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct drm_device *dev = node->minor->dev;
	struct drm_encoder *encoder;
	struct intel_encoder *intel_encoder;
	struct intel_digital_port *intel_dig_port;
	drm_modeset_lock_all(dev);
	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {
		intel_encoder = to_intel_encoder(encoder);
		if (intel_encoder->type != INTEL_OUTPUT_DISPLAYPORT)
			continue;
		intel_dig_port = enc_to_dig_port(encoder);
		if (!intel_dig_port->dp.can_mst)
			continue;
		seq_printf(m, "MST Source Port %c\n",
			   port_name(intel_dig_port->port));
		drm_dp_mst_dump_topology(m, &intel_dig_port->dp.mst_mgr);
	}
	drm_modeset_unlock_all(dev);
	return 0;
}
