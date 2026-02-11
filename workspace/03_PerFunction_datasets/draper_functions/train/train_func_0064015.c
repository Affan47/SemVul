xen_evtchn_mask_all(void)
{
	unsigned int evtchn;

	for (evtchn = 0; evtchn < xen_evtchn_nr_channels(); evtchn++)
		mask_evtchn(evtchn);
}
