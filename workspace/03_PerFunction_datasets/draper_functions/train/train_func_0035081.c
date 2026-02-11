tda1004x_check_upload_ok(struct tda1004x_state *state)
{
	u8 data1, data2;
	unsigned long timeout;

	if (state->demod_type == TDA1004X_DEMOD_TDA10046) {
		timeout = jiffies + 2 * HZ;
		while(!(tda1004x_read_byte(state, TDA1004X_STATUS_CD) & 0x20)) {
			if (time_after(jiffies, timeout)) {
				printk(KERN_ERR "tda1004x: timeout waiting for DSP ready\n");
				break;
			}
			msleep(1);
		}
	} else
		msleep(100);


	tda1004x_write_mask(state, TDA1004X_CONFC4, 0x10, 0);
	tda1004x_write_byteI(state, TDA1004X_DSP_CMD, 0x67);

	data1 = tda1004x_read_byte(state, TDA1004X_DSP_DATA1);
	data2 = tda1004x_read_byte(state, TDA1004X_DSP_DATA2);
	if (data1 != 0x67 || data2 < 0x20 || data2 > 0x2e) {
		printk(KERN_INFO "tda1004x: found firmware revision %x -- invalid\n", data2);
		return -EIO;
	}
	printk(KERN_INFO "tda1004x: found firmware revision %x -- ok\n", data2);
	return 0;
}
