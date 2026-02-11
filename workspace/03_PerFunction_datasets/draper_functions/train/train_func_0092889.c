get_selector_for_cpu (CPUFreqSelectorService *service,
		      guint                   cpu)
{
	if (!service->selectors[cpu]) {
		service->selectors[cpu] = cpufreq_selector_factory_create_selector (cpu);
		if (!service->selectors[cpu])
			return NULL;

		if (service->selectors_max < cpu)
			service->selectors_max = cpu;
	}

	return service->selectors[cpu];
}
