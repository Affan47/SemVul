get_key_hvr1110(struct IR_i2c *ir, enum rc_type *protocol,
			   u32 *scancode, u8 *toggle)
{
	unsigned char buf[5];


	if (5 != i2c_master_recv(ir->c, buf, 5))
		return -EIO;


	if (!(buf[0] & 0x80))
		return 0;


	*protocol = RC_TYPE_RC5;
	*scancode = RC_SCANCODE_RC5(buf[3] & 0x1f, buf[4] >> 2);
	*toggle = !!(buf[3] & 0x40);
	return 1;
}
