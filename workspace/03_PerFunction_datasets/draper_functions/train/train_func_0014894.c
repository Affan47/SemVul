hciops_stop_discovery(int index)
{
	struct dev_info *dev = &devs[index];

	DBG("index %d", index);

	switch (dev->discov_state) {
	case DISCOV_INQ:
		return hciops_stop_inquiry(index);
	case DISCOV_SCAN:
		return hciops_stop_scanning(index);
	case DISCOV_NAMES:
		cancel_resolve_name(index);
	default:
		return -EINVAL;
	}
}
