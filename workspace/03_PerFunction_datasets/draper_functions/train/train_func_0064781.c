acpi_processor_unregister_performance(unsigned int cpu)
{
	struct acpi_processor *pr;

	mutex_lock(&performance_mutex);

	pr = per_cpu(processors, cpu);
	if (!pr) {
		mutex_unlock(&performance_mutex);
		return;
	}

	if (pr->performance)
		kfree(pr->performance->states);
	pr->performance = NULL;

	mutex_unlock(&performance_mutex);

	return;
}
