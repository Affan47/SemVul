ext4_attr_store(struct kobject *kobj,
			       struct attribute *attr,
			       const char *buf, size_t len)
{
	struct ext4_sb_info *sbi = container_of(kobj, struct ext4_sb_info,
						s_kobj);
	struct ext4_attr *a = container_of(attr, struct ext4_attr, attr);
	void *ptr = calc_ptr(a, sbi);
	unsigned long t;
	int ret;

	switch (a->attr_id) {
	case attr_reserved_clusters:
		return reserved_clusters_store(a, sbi, buf, len);
	case attr_pointer_ui:
		if (!ptr)
			return 0;
		ret = kstrtoul(skip_spaces(buf), 0, &t);
		if (ret)
			return ret;
		*((unsigned int *) ptr) = t;
		return len;
	case attr_inode_readahead:
		return inode_readahead_blks_store(a, sbi, buf, len);
	case attr_trigger_test_error:
		return trigger_test_error(a, sbi, buf, len);
	}
	return 0;
}
