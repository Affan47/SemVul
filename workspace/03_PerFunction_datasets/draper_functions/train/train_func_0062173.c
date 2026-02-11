wait_for_bulk_out_ready(struct reader_dev *dev)
{
	int i, rc;
	int iobase = dev->p_dev->resource[0]->start;

	for (i = 0; i < POLL_LOOP_COUNT; i++) {
		if ((xinb(iobase + REG_OFFSET_BUFFER_STATUS)
		    & BSR_BULK_OUT_FULL) == 0) {
			DEBUGP(4, dev, "BulkOut empty (i=%d)\n", i);
			return 1;
		}
	}

	DEBUGP(4, dev, "wait_event_interruptible_timeout(timeout=%ld\n",
		dev->timeout);
	rc = wait_event_interruptible_timeout(dev->write_wait,
					      test_and_clear_bit(BS_WRITABLE,
						       &dev->buffer_status),
					      dev->timeout);

	if (rc > 0)
		DEBUGP(4, dev, "woke up: BulkOut empty\n");
	else if (rc == 0)
		DEBUGP(4, dev, "woke up: BulkOut full, returning 0 :(\n");
	else if (rc < 0)
		DEBUGP(4, dev, "woke up: signal arrived\n");

	return rc;
}
