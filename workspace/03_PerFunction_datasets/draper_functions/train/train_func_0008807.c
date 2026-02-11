max1363_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct max1363_state *st = iio_priv(indio_dev);
	s64 timestamp = iio_get_time_ns();
	unsigned long mask, loc;
	u8 rx;
	u8 tx[2] = { st->setupbyte,
		     MAX1363_MON_INT_ENABLE | (st->monitor_speed << 1) | 0xF0 };

	st->recv(st->client, &rx, 1);
	mask = rx;
	for_each_set_bit(loc, &mask, 8)
		iio_push_event(indio_dev, max1363_event_codes[loc], timestamp);
	st->send(st->client, tx, 2);

	return IRQ_HANDLED;
}
