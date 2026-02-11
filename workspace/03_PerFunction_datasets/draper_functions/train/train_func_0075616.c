ptp_dp83640_verify(struct ptp_clock_info *ptp, unsigned int pin,
			      enum ptp_pin_function func, unsigned int chan)
{
	struct dp83640_clock *clock =
		container_of(ptp, struct dp83640_clock, caps);

	if (clock->caps.pin_config[pin].func == PTP_PF_PHYSYNC &&
	    !list_empty(&clock->phylist))
		return 1;

	if (func == PTP_PF_PHYSYNC)
		return 1;

	return 0;
}
