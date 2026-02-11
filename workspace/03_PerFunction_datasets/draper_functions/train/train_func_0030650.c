img_ir_sanyo_scancode(int len, u64 raw, u64 enabled_protocols,
				 struct img_ir_scancode_req *request)
{
	unsigned int addr, addr_inv, data, data_inv;

	if (!len)
		return IMG_IR_REPEATCODE;
	if (len != 42)
		return -EINVAL;
	addr     = (raw >>  0) & 0x1fff;
	addr_inv = (raw >> 13) & 0x1fff;
	data     = (raw >> 26) & 0xff;
	data_inv = (raw >> 34) & 0xff;

	if ((data_inv ^ data) != 0xff)
		return -EINVAL;

	if ((addr_inv ^ addr) != 0x1fff)
		return -EINVAL;


	request->protocol = RC_TYPE_SANYO;
	request->scancode = addr << 8 | data;
	return IMG_IR_SCANCODE;
}
