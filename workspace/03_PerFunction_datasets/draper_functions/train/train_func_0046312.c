initialize_first_module (TrackerMimetypeInfo *info)
{
	ModuleInfo *module_info = NULL;


	while (info->cur && !module_info) {
		module_info = load_module (info->cur->data, TRUE);

		if (!module_info) {
			info->cur = info->cur->next;
		}
	}

	info->cur_module_info = module_info;
	return (info->cur_module_info != NULL);
}
