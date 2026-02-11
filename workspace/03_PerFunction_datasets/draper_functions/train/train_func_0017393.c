get_fam15h_addr(u32 addr)
{
	switch (addr) {
	case MSR_K7_PERFCTR0:
	case MSR_K7_PERFCTR1:
	case MSR_K7_PERFCTR2:
	case MSR_K7_PERFCTR3:
		return MSR_F15H_PERF_CTR + (addr - MSR_K7_PERFCTR0);
	case MSR_K7_EVNTSEL0:
	case MSR_K7_EVNTSEL1:
	case MSR_K7_EVNTSEL2:
	case MSR_K7_EVNTSEL3:
		return MSR_F15H_PERF_CTL + (addr - MSR_K7_EVNTSEL0);
	default:
		break;
	}

	return addr;
}
