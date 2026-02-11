skl_get_total_relative_data_rate(struct intel_crtc *intel_crtc,
				 const struct skl_pipe_wm_parameters *params)
{
	unsigned int total_data_rate = 0;
	int plane;

	for (plane = 0; plane < intel_num_planes(intel_crtc); plane++) {
		const struct intel_plane_wm_parameters *p;

		p = &params->plane[plane];
		if (!p->enabled)
			continue;

		total_data_rate += skl_plane_relative_data_rate(p, 0);
		if (p->y_bytes_per_pixel) {
			total_data_rate += skl_plane_relative_data_rate(p, 1);
		}
	}

	return total_data_rate;
}
