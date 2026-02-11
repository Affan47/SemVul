kmod_module_info_get_value(const struct kmod_list *entry)
{
	struct kmod_module_info *info;

	if (entry == NULL)
		return NULL;

	info = entry->data;
	return info->value;
}
