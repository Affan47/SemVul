efuse_one_byte_rw(struct _adapter *padapter, u8 bRead, u16 addr,
			    u8 *data)
{
	u8 tmpidx = 0, tmpv8 = 0, bResult;


	r8712_write8(padapter, EFUSE_CTRL + 1, (u8)(addr & 0xFF));
	tmpv8 = ((u8)((addr >> 8) & 0x03)) |
		 (r8712_read8(padapter, EFUSE_CTRL + 2) & 0xFC);
	r8712_write8(padapter, EFUSE_CTRL + 2, tmpv8);
	if (bRead) {
		r8712_write8(padapter, EFUSE_CTRL + 3,  0x72);
		while (!(0x80 & r8712_read8(padapter, EFUSE_CTRL + 3)) &&
		       (tmpidx < 100))
			tmpidx++;
		if (tmpidx < 100) {
			*data = r8712_read8(padapter, EFUSE_CTRL);
			bResult = true;
		} else {
			*data = 0;
			bResult = false;
		}
	} else {
		r8712_write8(padapter, EFUSE_CTRL, *data);
		r8712_write8(padapter, EFUSE_CTRL + 3, 0xF2);
		while ((0x80 & r8712_read8(padapter, EFUSE_CTRL + 3)) &&
		       (tmpidx < 100))
			tmpidx++;
		if (tmpidx < 100)
			bResult = true;
		else
			bResult = false;
	}
	return bResult;
}
