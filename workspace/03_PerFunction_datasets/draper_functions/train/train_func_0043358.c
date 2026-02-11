hciops_disable_cod_cache(int index)
{
	struct dev_info *dev = &devs[index];

	DBG("hci%d cache_enable %d", index, dev->cache_enable);

	if (!dev->cache_enable)
		return 0;

	DBG("hci%d current_cod 0x%06x wanted_cod 0x%06x", index,
					dev->current_cod, dev->wanted_cod);


	dev->cache_enable = FALSE;

	if (dev->current_cod == dev->wanted_cod) {
		update_ext_inquiry_response(index);
		return 0;
	}

	return write_class(index, dev->wanted_cod);
}
