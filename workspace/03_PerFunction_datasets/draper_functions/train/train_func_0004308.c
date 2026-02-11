intel_get_cxsr_latency(int is_desktop,
							 int is_ddr3,
							 int fsb,
							 int mem)
{
	const struct cxsr_latency *latency;
	int i;

	if (fsb == 0 || mem == 0)
		return NULL;

	for (i = 0; i < ARRAY_SIZE(cxsr_latency_table); i++) {
		latency = &cxsr_latency_table[i];
		if (is_desktop == latency->is_desktop &&
		    is_ddr3 == latency->is_ddr3 &&
		    fsb == latency->fsb_freq && mem == latency->mem_freq)
			return latency;
	}

	DRM_DEBUG_KMS("Unknown FSB/MEM found, disable CxSR\n");

	return NULL;
}
