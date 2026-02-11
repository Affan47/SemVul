first_policy(bool active)
{
	struct cpufreq_policy *policy;


	if (list_empty(&cpufreq_policy_list))
		return NULL;

	policy = list_first_entry(&cpufreq_policy_list, typeof(*policy),
				  policy_list);

	if (!suitable_policy(policy, active))
		policy = next_policy(policy, active);

	return policy;
}
