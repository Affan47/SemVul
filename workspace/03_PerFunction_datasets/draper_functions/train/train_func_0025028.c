enabled_store(struct kobject *kobj,
			     struct kobj_attribute *attr,
			     const char *buf, size_t count)
{
	ssize_t ret;

	ret = double_flag_store(kobj, attr, buf, count,
				TRANSPARENT_HUGEPAGE_FLAG,
				TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG);

	if (ret > 0) {
		int err;

		mutex_lock(&khugepaged_mutex);
		err = start_stop_khugepaged();
		mutex_unlock(&khugepaged_mutex);

		if (err)
			ret = err;
	}

	return ret;
}
