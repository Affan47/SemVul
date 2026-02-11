init_hypervisor(struct cpuinfo_x86 *c)
{
	if (x86_hyper && x86_hyper->set_cpu_features)
		x86_hyper->set_cpu_features(c);
}
