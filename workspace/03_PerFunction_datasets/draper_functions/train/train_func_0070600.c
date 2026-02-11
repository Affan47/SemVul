xen_amd_read_pmc(int counter)
{
	struct xen_pmu_amd_ctxt *ctxt;
	uint64_t *counter_regs;
	struct xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uint8_t xenpmu_flags = get_xenpmu_flags();

	if (!xenpmu_data || !(xenpmu_flags & XENPMU_IRQ_PROCESSING)) {
		uint32_t msr;
		int err;

		msr = amd_counters_base + (counter * amd_msr_step);
		return native_read_msr_safe(msr, &err);
	}

	ctxt = &xenpmu_data->pmu.c.amd;
	counter_regs = field_offset(ctxt, counters);
	return counter_regs[counter];
}
