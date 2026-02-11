__max1363_check_event_mask(int thismask, int checkmask)
{
	int ret = 0;

	if (thismask < 4) {
		if (checkmask & ~0x0F) {
			ret = -EBUSY;
			goto error_ret;
		}
	} else if (thismask < 6) {
		if (checkmask & ~0x30) {
			ret = -EBUSY;
			goto error_ret;
		}
	} else if (checkmask & ~0xC0)
		ret = -EBUSY;
error_ret:
	return ret;
}
