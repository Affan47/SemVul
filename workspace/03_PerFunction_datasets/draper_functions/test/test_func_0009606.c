iio_trigger_poll(struct iio_trigger *trig)
{
	int i;

	if (!atomic_read(&trig->use_count)) {
		atomic_set(&trig->use_count, CONFIG_IIO_CONSUMERS_PER_TRIGGER);

		for (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) {
			if (trig->subirqs[i].enabled)
				generic_handle_irq(trig->subirq_base + i);
			else
				iio_trigger_notify_done(trig);
		}
	}
}
