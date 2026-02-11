hv_do_hypercall(u64 control, void *input, void *output)
{
	u64 input_address = (input) ? virt_to_phys(input) : 0;
	u64 output_address = (output) ? virt_to_phys(output) : 0;
	void *hypercall_page = hv_context.hypercall_page;
#ifdef CONFIG_X86_64
	u64 hv_status = 0;

	if (!hypercall_page)
		return (u64)ULLONG_MAX;

	__asm__ __volatile__("mov %0, %%r8" : : "r" (output_address) : "r8");
	__asm__ __volatile__(CALL_NOSPEC :
			     "=a" (hv_status) :
			     "c" (control), "d" (input_address),
			     THUNK_TARGET(hypercall_page));

	return hv_status;

#else

	u32 control_hi = control >> 32;
	u32 control_lo = control & 0xFFFFFFFF;
	u32 hv_status_hi = 1;
	u32 hv_status_lo = 1;
	u32 input_address_hi = input_address >> 32;
	u32 input_address_lo = input_address & 0xFFFFFFFF;
	u32 output_address_hi = output_address >> 32;
	u32 output_address_lo = output_address & 0xFFFFFFFF;

	if (!hypercall_page)
		return (u64)ULLONG_MAX;

	__asm__ __volatile__ (CALL_NOSPEC : "=d"(hv_status_hi),
			      "=a"(hv_status_lo) : "d" (control_hi),
			      "a" (control_lo), "b" (input_address_hi),
			      "c" (input_address_lo), "D"(output_address_hi),
			      "S"(output_address_lo),
			      THUNK_TARGET(hypercall_page));

	return hv_status_lo | ((u64)hv_status_hi << 32);
#endif
}
