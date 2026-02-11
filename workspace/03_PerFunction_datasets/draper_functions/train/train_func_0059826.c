_filter_device (vector blist, vector elist, char * vendor, char * product)
{
	if (!vendor || !product)
		return 0;
	if (_blacklist_exceptions_device(elist, vendor, product))
		return MATCH_DEVICE_BLIST_EXCEPT;
	if (_blacklist_device(blist, vendor, product))
		return MATCH_DEVICE_BLIST;
	return 0;
}
