compat_agpioc_unbind_wrap(struct agp_file_private *priv, void __user *arg)
{
	struct agp_memory *memory;
	struct agp_unbind32 unbind;

	DBG("");
	if (copy_from_user(&unbind, arg, sizeof(unbind)))
		return -EFAULT;

	memory = agp_find_mem_by_key(unbind.key);

	if (memory == NULL)
		return -EINVAL;

	return agp_unbind_memory(memory);
}
