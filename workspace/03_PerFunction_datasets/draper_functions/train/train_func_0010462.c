ttusb_i2c_msg(struct ttusb *ttusb,
		  u8 addr, u8 * snd_buf, u8 snd_len, u8 * rcv_buf,
		  u8 rcv_len)
{
	u8 b[0x28];
	u8 id = ++ttusb->c;
	int i, err;

	if (snd_len > 0x28 - 7 || rcv_len > 0x20 - 7)
		return -EINVAL;

	b[0] = 0xaa;
	b[1] = id;
	b[2] = 0x31;
	b[3] = snd_len + 3;
	b[4] = addr << 1;
	b[5] = snd_len;
	b[6] = rcv_len;

	for (i = 0; i < snd_len; i++)
		b[7 + i] = snd_buf[i];

	err = ttusb_cmd(ttusb, b, snd_len + 7, 1);

	if (err)
		return -EREMOTEIO;

	err = ttusb_result(ttusb, b, 0x20);


	if ((snd_len != b[5]) || (rcv_len != b[6])) return -EREMOTEIO;

	if (rcv_len > 0) {

		if (err || b[0] != 0x55 || b[1] != id) {
			dprintk
			    ("%s: usb_bulk_msg(recv) failed, err == %i, id == %02x, b == ",
			     __func__, err, id);
			return -EREMOTEIO;
		}

		for (i = 0; i < rcv_len; i++)
			rcv_buf[i] = b[7 + i];
	}

	return rcv_len;
}
