i9xx_get_aux_clock_divider(struct intel_dp *intel_dp, int index)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;


	return index ? 0 : intel_hrawclk(dev) / 2;
}
