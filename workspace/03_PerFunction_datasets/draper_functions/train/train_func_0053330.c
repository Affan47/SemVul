xen_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = this_cpu_ptr(&xen_clock_events.evt);
	irqreturn_t ret;

	ret = IRQ_NONE;
	if (evt->event_handler) {
		evt->event_handler(evt);
		ret = IRQ_HANDLED;
	}

	do_stolen_accounting();

	return ret;
}
