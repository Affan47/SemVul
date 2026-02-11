thread_exit()
{
	ResourceManager *pinst;

	pinst = ResourceManager::instance();
	if (pinst == NULL)
		return;

	global_lock(mtx_globj_);
	glob_objs_.erase(pinst);
	global_unlock(mtx_globj_);
	TlsWrapper<ResourceManager>::set_tls_obj(NULL);


	delete pinst;
}
