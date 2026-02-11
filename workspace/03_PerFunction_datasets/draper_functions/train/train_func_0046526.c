istgt_lu_islun2lun(uint64_t islun)
{
	uint64_t fmt_lun;
	uint64_t method;
	int lun_i;

	fmt_lun = islun;
	method = (fmt_lun >> 62) & 0x03U;
	fmt_lun = fmt_lun >> 48;
	if (method == 0x00U) {
		lun_i = (int) (fmt_lun & 0x00ffU);
	} else if (method == 0x01U) {
		lun_i = (int) (fmt_lun & 0x3fffU);
	} else {
		lun_i = 0xffffU;
	}
	return lun_i;
}
