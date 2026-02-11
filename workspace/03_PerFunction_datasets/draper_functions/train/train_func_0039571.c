ask_uint16(struct fdisk_context *cxt,
		uint16_t dflt, char *mesg)
{
	uintmax_t res;

	if (fdisk_ask_number(cxt, min(dflt, (uint16_t) 1),
				dflt, UINT16_MAX, mesg, &res) == 0)
		return res;
	return dflt;
}
