get_key_knc1(struct IR_i2c *ir, enum rc_type *protocol,
			u32 *scancode, u8 *toggle)
{
	unsigned char b;


	if (1 != i2c_master_recv(ir->c, &b, 1)) {
		dprintk(1,"read error\n");
		return -EIO;
	}


	dprintk(2,"key %02x\n", b);

	if (b == 0xff)
		return 0;

	if (b == 0xfe)

		return 1;

	*protocol = RC_TYPE_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	return 1;
}
