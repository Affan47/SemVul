as3935_event_work(struct work_struct *work)
{
	struct as3935_state *st;
	int val;

	st = container_of(work, struct as3935_state, work.work);

	as3935_read(st, AS3935_INT, &val);
	val &= AS3935_INT_MASK;

	switch (val) {
	case AS3935_EVENT_INT:
		iio_trigger_poll(st->trig);
		break;
	case AS3935_NOISE_INT:
		dev_warn(&st->spi->dev, "noise level is too high");
		break;
	}
}
