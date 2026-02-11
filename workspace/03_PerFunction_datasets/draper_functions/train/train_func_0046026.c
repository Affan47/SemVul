retrigger_dynirq(struct irq_data *data)
{
	unsigned int evtchn = evtchn_from_irq(data->irq);
	int masked;

	if (!VALID_EVTCHN(evtchn))
		return 0;

	masked = test_and_set_mask(evtchn);
	set_evtchn(evtchn);
	if (!masked)
		unmask_evtchn(evtchn);

	return 1;
}
