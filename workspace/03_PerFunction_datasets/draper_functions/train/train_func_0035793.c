atomics_cobalt_device_set_simulation (dc_device_t *abstract, unsigned int simulation)
{
	atomics_cobalt_device_t *device = (atomics_cobalt_device_t *) abstract;

	if (!ISINSTANCE (abstract))
		return DC_STATUS_INVALIDARGS;

	device->simulation = simulation;

	return DC_STATUS_SUCCESS;
}
