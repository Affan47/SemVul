psb_intel_sdvo_select_i2c_bus(struct drm_psb_private *dev_priv,
			  struct psb_intel_sdvo *sdvo, u32 reg)
{
	struct sdvo_device_mapping *mapping;
	u8 pin, speed;

	if (IS_SDVOB(reg))
		mapping = &dev_priv->sdvo_mappings[0];
	else
		mapping = &dev_priv->sdvo_mappings[1];

	pin = GMBUS_PORT_DPB;
	speed = GMBUS_RATE_1MHZ >> 8;
	if (mapping->initialized) {
		pin = mapping->i2c_pin;
		speed = mapping->i2c_speed;
	}

	if (pin < GMBUS_NUM_PORTS) {
		sdvo->i2c = &dev_priv->gmbus[pin].adapter;
		gma_intel_gmbus_set_speed(sdvo->i2c, speed);
		gma_intel_gmbus_force_bit(sdvo->i2c, true);
	} else
		sdvo->i2c = &dev_priv->gmbus[GMBUS_PORT_DPB].adapter;
}
