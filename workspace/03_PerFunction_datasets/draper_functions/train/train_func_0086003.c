get_ibs_lvt_offset(void)
{
	u64 val;

	rdmsrl(MSR_AMD64_IBSCTL, val);
	if (!(val & IBSCTL_LVT_OFFSET_VALID))
		return -EINVAL;

	return val & IBSCTL_LVT_OFFSET_MASK;
}
