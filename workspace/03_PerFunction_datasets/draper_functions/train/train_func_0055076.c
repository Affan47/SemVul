get_all_delsys(int aid, char *dest, int max_size)
{
	int i, len;
	adapter *ad = get_adapter_nw(aid);
	dest[0] = 0;
	len = 0;
	if (!ad)
		return dest;

	for (i = 0; i < MAX_DELSYS; i++)
		if (ad->sys[i] > 0)
			len += snprintf(dest + len, max_size - len, "%s,",
					get_delsys(ad->sys[i]));

	if (len > 0)
		dest[len - 1] = 0;

	return dest;
}
