ql_get_both_serdes(struct ql_adapter *qdev, u32 addr,
			u32 *direct_ptr, u32 *indirect_ptr,
			unsigned int direct_valid, unsigned int indirect_valid)
{
	unsigned int status;

	status = 1;
	if (direct_valid)
		status = ql_read_serdes_reg(qdev, addr, direct_ptr);

	if (status)
		*direct_ptr = 0xDEADBEEF;

	status = 1;
	if (indirect_valid)
		status = ql_read_other_func_serdes_reg(
						qdev, addr, indirect_ptr);

	if (status)
		*indirect_ptr = 0xDEADBEEF;
}
