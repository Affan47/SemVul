wl1251_event_wait(struct wl1251 *wl, u32 mask, int timeout_ms)
{
	u32 events_vector, event;
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(timeout_ms);

	do {
		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;

		msleep(1);


		wl1251_mem_read(wl, wl->mbox_ptr[0], &events_vector,
				sizeof(events_vector));
		event = events_vector & mask;
		wl1251_mem_read(wl, wl->mbox_ptr[1], &events_vector,
				sizeof(events_vector));
		event |= events_vector & mask;
	} while (!event);

	return 0;
}
