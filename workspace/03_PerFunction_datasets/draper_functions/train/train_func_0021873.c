gov_cancel_work(struct dbs_data *dbs_data,
		struct cpufreq_policy *policy)
{
	struct cpu_dbs_info *cdbs;
	int i;

	for_each_cpu(i, policy->cpus) {
		cdbs = dbs_data->cdata->get_cpu_cdbs(i);
		cancel_delayed_work_sync(&cdbs->dwork);
	}
}
