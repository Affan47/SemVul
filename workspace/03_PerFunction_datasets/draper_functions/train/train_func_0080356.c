__sst_wait_idle(u8 __iomem *vbase)
{
	int count = 0;


	while(1) {
		if (__sst_read(vbase, STATUS) & STATUS_FBI_BUSY) {
			f_dddprintk("status: busy\n");


			count = 0;
		} else {
			count++;
			f_dddprintk("status: idle(%d)\n", count);
		}
		if (count >= 5) return 1;

	}
}
