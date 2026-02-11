free_common_dbs_info(struct cpufreq_policy *policy,
				 struct common_dbs_data *cdata)
{
	struct cpu_dbs_info *cdbs = cdata->get_cpu_cdbs(policy->cpu);
	struct cpu_common_dbs_info *shared = cdbs->shared;
	int j;

	for_each_cpu(j, policy->cpus)
		cdata->get_cpu_cdbs(j)->shared = NULL;

	kfree(shared);
}
