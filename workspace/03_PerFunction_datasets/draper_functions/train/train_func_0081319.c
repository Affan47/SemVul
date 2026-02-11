pinst_has_cpu(struct padata_instance *pinst, int cpu)
{
	return cpumask_test_cpu(cpu, pinst->cpumask.pcpu) ||
		cpumask_test_cpu(cpu, pinst->cpumask.cbcpu);
}
