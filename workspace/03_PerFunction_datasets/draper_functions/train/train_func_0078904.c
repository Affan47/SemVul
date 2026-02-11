xen_hyper_test_pcpu_id(uint pcpu_id)
{
	ulong *cpumask = xht->cpumask;
	uint i, j;

	if (pcpu_id == XEN_HYPER_PCPU_ID_INVALID ||
	pcpu_id > XEN_HYPER_MAX_CPUS()) {
		return FALSE;
	}

	i = pcpu_id / (sizeof(ulong) * 8);
	j = pcpu_id % (sizeof(ulong) * 8);
	cpumask += i;
	if (*cpumask & (1UL << j)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
