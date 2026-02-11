r8712_efuse_access(struct _adapter *padapter, u8 bRead, u16 start_addr,
		      u16 cnts, u8 *data)
{
	int i;
	u8 res = true;

	if (start_addr > EFUSE_MAX_SIZE)
		return false;
	if (!bRead && ((start_addr + cnts) >
	   efuse_available_max_size))
		return false;
	if (!bRead && !r8712_efuse_reg_init(padapter))
		return false;

	for (i = 0; i < cnts; i++) {
		if ((start_addr + i) > EFUSE_MAX_SIZE) {
			res = false;
			break;
		}
		res = efuse_one_byte_rw(padapter, bRead, start_addr + i,
		      data + i);
		if (!bRead && !res)
			break;
	}
	if (!bRead)
		r8712_efuse_reg_uninit(padapter);
	return res;
}
