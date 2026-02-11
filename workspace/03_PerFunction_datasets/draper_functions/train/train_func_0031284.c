find_last_devid_from_ivhd(struct ivhd_header *h)
{
	u8 *p = (void *)h, *end = (void *)h;
	struct ivhd_entry *dev;

	p += sizeof(*h);
	end += h->length;

	while (p < end) {
		dev = (struct ivhd_entry *)p;
		switch (dev->type) {
		case IVHD_DEV_ALL:

			update_last_devid(0xffff);
			break;
		case IVHD_DEV_SELECT:
		case IVHD_DEV_RANGE_END:
		case IVHD_DEV_ALIAS:
		case IVHD_DEV_EXT_SELECT:

			update_last_devid(dev->devid);
			break;
		default:
			break;
		}
		p += ivhd_entry_length(p);
	}

	WARN_ON(p != end);

	return 0;
}
