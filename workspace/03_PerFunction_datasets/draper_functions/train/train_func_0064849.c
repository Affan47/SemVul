cs_check_cpu(int cpu, unsigned int load)
{
	struct cs_cpu_dbs_info_s *dbs_info = &per_cpu(cs_cpu_dbs_info, cpu);
	struct cpufreq_policy *policy = dbs_info->cdbs.shared->policy;
	struct dbs_data *dbs_data = policy->governor_data;
	struct cs_dbs_tuners *cs_tuners = dbs_data->tuners;


	if (cs_tuners->freq_step == 0)
		return;


	if (load > cs_tuners->up_threshold) {
		dbs_info->down_skip = 0;


		if (dbs_info->requested_freq == policy->max)
			return;

		dbs_info->requested_freq += get_freq_target(cs_tuners, policy);

		if (dbs_info->requested_freq > policy->max)
			dbs_info->requested_freq = policy->max;

		__cpufreq_driver_target(policy, dbs_info->requested_freq,
			CPUFREQ_RELATION_H);
		return;
	}


	if (++dbs_info->down_skip < cs_tuners->sampling_down_factor)
		return;
	dbs_info->down_skip = 0;


	if (load < cs_tuners->down_threshold) {
		unsigned int freq_target;


		if (policy->cur == policy->min)
			return;

		freq_target = get_freq_target(cs_tuners, policy);
		if (dbs_info->requested_freq > freq_target)
			dbs_info->requested_freq -= freq_target;
		else
			dbs_info->requested_freq = policy->min;

		__cpufreq_driver_target(policy, dbs_info->requested_freq,
				CPUFREQ_RELATION_L);
		return;
	}
}
