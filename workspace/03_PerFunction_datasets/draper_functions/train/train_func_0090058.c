sf1_read(struct adapter *adapter, unsigned int byte_cnt, int cont,
		    u32 *valp)
{
	int ret;

	if (!byte_cnt || byte_cnt > 4)
		return -EINVAL;
	if (t3_read_reg(adapter, A_SF_OP) & F_BUSY)
		return -EBUSY;
	t3_write_reg(adapter, A_SF_OP, V_CONT(cont) | V_BYTECNT(byte_cnt - 1));
	ret = t3_wait_op_done(adapter, A_SF_OP, F_BUSY, 0, SF_ATTEMPTS, 10);
	if (!ret)
		*valp = t3_read_reg(adapter, A_SF_DATA);
	return ret;
}
