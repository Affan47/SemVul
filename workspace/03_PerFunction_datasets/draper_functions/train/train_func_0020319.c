generate_pbl_cmd(void)
{
	uint32_t val = next_pbl_cmd;
	next_pbl_cmd += 0x40;
	int i;

	for (i = 3; i >= 0; i--) {
		*pmem_buf++ = (val >> (i * 8)) & 0xff;
		pbl_size++;
	}
}
