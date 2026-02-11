profiling_store(struct kobject *kobj,
				   struct kobj_attribute *attr,
				   const char *buf, size_t count)
{
	int ret;

	if (prof_on)
		return -EEXIST;


	profile_setup((char *)buf);
	ret = profile_init();
	if (ret)
		return ret;
	ret = create_proc_profile();
	if (ret)
		return ret;
	return count;
}
