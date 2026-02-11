uwb_rc_neh_grok(struct uwb_rc *rc, void *buf, size_t buf_size)
{
	struct device *dev = &rc->uwb_dev.dev;
	void *itr;
	struct uwb_rceb *rceb;
	size_t size, real_size, event_size;
	int needtofree;

	itr = buf;
	size = buf_size;
	while (size > 0) {
		if (size < sizeof(*rceb)) {
			dev_err(dev, "not enough data in event buffer to "
				"process incoming events (%zu left, minimum is "
				"%zu)\n", size, sizeof(*rceb));
			break;
		}

		rceb = itr;
		if (rc->filter_event) {
			needtofree = rc->filter_event(rc, &rceb, size,
						      &real_size, &event_size);
			if (needtofree < 0 && needtofree != -ENOANO) {
				dev_err(dev, "BUG: Unable to filter event "
					"(0x%02x/%04x/%02x) from "
					"device. \n", rceb->bEventType,
					le16_to_cpu(rceb->wEvent),
					rceb->bEventContext);
				break;
			}
		} else
			needtofree = -ENOANO;


		if (needtofree == -ENOANO) {
			ssize_t ret = uwb_est_find_size(rc, rceb, size);
			if (ret < 0)
				break;
			if (ret > size) {
				dev_err(dev, "BUG: hw sent incomplete event "
					"0x%02x/%04x/%02x (%zd bytes), only got "
					"%zu bytes. We don't handle that.\n",
					rceb->bEventType, le16_to_cpu(rceb->wEvent),
					rceb->bEventContext, ret, size);
				break;
			}
			real_size = event_size = ret;
		}
		uwb_rc_neh_grok_event(rc, rceb, event_size);

		if (needtofree == 1)
			kfree(rceb);

		itr += real_size;
		size -= real_size;
	}
}
