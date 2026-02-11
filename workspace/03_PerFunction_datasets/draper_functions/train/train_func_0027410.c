__stmpe_block_read(struct stmpe *stmpe, u8 reg, u8 length,
			      u8 *values)
{
	int ret;

	ret = stmpe->ci->read_block(stmpe, reg, length, values);
	if (ret < 0)
		dev_err(stmpe->dev, "failed to read regs %#x: %d\n", reg, ret);

	dev_vdbg(stmpe->dev, "rd: reg %#x (%d) => ret %#x\n", reg, length, ret);
	stmpe_dump_bytes("stmpe rd: ", values, length);

	return ret;
}
