zr36060_wait_end (struct zr36060 *ptr)
{
	int i = 0;

	while (zr36060_read_status(ptr) & ZR060_CFSR_Busy) {
		udelay(1);
		if (i++ > 200000) {
			dprintk(1,
				"%s: timeout at wait_end (last status: 0x%02x)\n",
				ptr->name, ptr->status);
			break;
		}
	}
}
