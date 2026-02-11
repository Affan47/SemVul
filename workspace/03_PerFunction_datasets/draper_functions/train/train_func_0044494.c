pt_read_offset(struct pt_buffer *buf)
{
	u64 offset, base_topa;

	rdmsrl(MSR_IA32_RTIT_OUTPUT_BASE, base_topa);
	buf->cur = phys_to_virt(base_topa);

	rdmsrl(MSR_IA32_RTIT_OUTPUT_MASK, offset);

	buf->output_off = offset >> 32;

	buf->cur_idx = (offset & 0xffffff80) >> 7;
}
