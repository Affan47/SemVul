clockevent_i8253_init(bool oneshot)
{
	if (oneshot) {
		i8253_clockevent.features |= CLOCK_EVT_FEAT_ONESHOT;
		i8253_clockevent.set_state_oneshot = pit_set_oneshot;
	}


	i8253_clockevent.cpumask = cpumask_of(smp_processor_id());

	clockevents_config_and_register(&i8253_clockevent, PIT_TICK_RATE,
					0xF, 0x7FFF);
}
