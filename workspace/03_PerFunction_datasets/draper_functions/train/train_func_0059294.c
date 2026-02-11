cstate_init(void)
{

	switch (boot_cpu_data.x86_model) {
	case 55:
	case 76:
	case 77:
		pkg_msr[PERF_CSTATE_PKG_C6_RES].msr = MSR_PKG_C7_RESIDENCY;
	}

	if (cstate_probe_msr(core_msr, core_events_attrs, PERF_CSTATE_CORE_EVENT_MAX))
		has_cstate_core = true;

	if (cstate_probe_msr(pkg_msr, pkg_events_attrs, PERF_CSTATE_PKG_EVENT_MAX))
		has_cstate_pkg = true;

	return (has_cstate_core || has_cstate_pkg) ? 0 : -ENODEV;
}
