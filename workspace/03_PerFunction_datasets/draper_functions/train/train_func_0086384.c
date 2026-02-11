finished_loading(const char *name)
{
	struct module *mod;
	bool ret;


	sched_annotate_sleep();
	mutex_lock(&module_mutex);
	mod = find_module_all(name, strlen(name), true);
	ret = !mod || mod->state == MODULE_STATE_LIVE
		|| mod->state == MODULE_STATE_GOING;
	mutex_unlock(&module_mutex);

	return ret;
}
