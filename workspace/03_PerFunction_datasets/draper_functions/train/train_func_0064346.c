trace_define_common_fields(void)
{
	int ret;
	struct trace_entry ent;

	__common_field(unsigned short, type);
	__common_field(unsigned char, flags);
	__common_field(unsigned char, preempt_count);
	__common_field(int, pid);

	return ret;
}
