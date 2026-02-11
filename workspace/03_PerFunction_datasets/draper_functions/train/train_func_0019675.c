dib9000_mbx_send_attr(struct dib9000_state *state, u8 id, u16 * data, u8 len, u16 attr)
{
	u8 *d, b[2];
	u16 tmp;
	u16 size;
	u32 i;
	int ret = 0;

	if (!state->platform.risc.fw_is_running)
		return -EINVAL;

	if (mutex_lock_interruptible(&state->platform.risc.mbx_if_lock) < 0) {
		dprintk("could not get the lock");
		return -EINTR;
	}
	tmp = MAX_MAILBOX_TRY;
	do {
		size = dib9000_read_word_attr(state, 1043, attr) & 0xff;
		if ((size + len + 1) > MBX_MAX_WORDS && --tmp) {
			dprintk("MBX: RISC mbx full, retrying");
			msleep(100);
		} else
			break;
	} while (1);


	if (tmp == 0) {
		ret = -EINVAL;
		goto out;
	}
#ifdef DUMP_MSG
	dprintk("--> %02x %d ", id, len + 1);
	for (i = 0; i < len; i++)
		dprintk("%04x ", data[i]);
	dprintk("\n");
#endif


	d = (u8 *) data;
	for (i = 0; i < len; i++) {
		tmp = data[i];
		*d++ = tmp >> 8;
		*d++ = tmp & 0xff;
	}


	b[0] = id;
	b[1] = len + 1;
	if (dib9000_write16_noinc_attr(state, 1045, b, 2, attr) != 0 || dib9000_write16_noinc_attr(state, 1045, (u8 *) data, len * 2, attr) != 0) {
		ret = -EIO;
		goto out;
	}


	ret = (u8) dib9000_write_word_attr(state, 1043, 1 << 14, attr);

out:
	mutex_unlock(&state->platform.risc.mbx_if_lock);

	return ret;
}
