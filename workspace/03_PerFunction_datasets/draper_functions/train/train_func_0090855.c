tracker_extract_module_manager_get_for_mimetype (const gchar                  *mimetype,
                                                 TrackerExtractInitFunc       *init_func,
                                                 TrackerExtractShutdownFunc   *shutdown_func,
                                                 TrackerExtractMetadataFunc   *extract_func)
{
	ModuleInfo *module_info = NULL;
	GList *mimetype_rules;

	if (init_func) {
		*init_func = NULL;
	}

	if (shutdown_func) {
		*shutdown_func = NULL;
	}

	if (extract_func) {
		*extract_func = NULL;
	}

	if (!initialized &&
	    !tracker_extract_module_manager_init ()) {
		return NULL;
	}

	mimetype_rules = lookup_rules (mimetype);

	if (!mimetype_rules) {
		return NULL;
	}

	module_info = load_module (mimetype_rules->data, FALSE);

	if (!module_info) {
		return NULL;
	}

	if (extract_func) {
		*extract_func = module_info->extract_func;
	}

	if (init_func) {
		*init_func = module_info->init_func;
	}

	if (shutdown_func) {
		*shutdown_func = module_info->shutdown_func;
	}

	return module_info->module;
}
