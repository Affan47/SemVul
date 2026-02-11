cpufreq_sysfs_release(struct kobject *kobj)
{
	struct cpufreq_policy *policy = to_policy(kobj);
	pr_debug("last reference is dropped\n");
	complete(&policy->kobj_unregister);
}
