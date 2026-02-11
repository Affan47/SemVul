library_deinit()
{
	private_library_t *this = (private_library_t*)lib;
	bool detailed;

	if (!this || !ref_put(&this->ref))
	{
		return;
	}

	detailed = lib->settings->get_bool(lib->settings,
								"%s.leak_detective.detailed", TRUE, lib->ns);


	lib->credmgr->flush_cache(lib->credmgr, CERT_ANY);

	this->public.streams->destroy(this->public.streams);
	this->public.watcher->destroy(this->public.watcher);
	this->public.scheduler->destroy(this->public.scheduler);
	this->public.processor->destroy(this->public.processor);
	this->public.plugins->destroy(this->public.plugins);
	this->public.hosts->destroy(this->public.hosts);
	this->public.settings->destroy(this->public.settings);
	this->public.credmgr->destroy(this->public.credmgr);
	this->public.creds->destroy(this->public.creds);
	this->public.encoding->destroy(this->public.encoding);
	this->public.crypto->destroy(this->public.crypto);
	this->public.caps->destroy(this->public.caps);
	this->public.proposal->destroy(this->public.proposal);
	this->public.fetcher->destroy(this->public.fetcher);
	this->public.resolver->destroy(this->public.resolver);
	this->public.db->destroy(this->public.db);
	this->public.printf_hook->destroy(this->public.printf_hook);
	this->objects->destroy(this->objects);
	if (this->public.integrity)
	{
		this->public.integrity->destroy(this->public.integrity);
	}

	if (lib->leak_detective)
	{
		lib->leak_detective->report(lib->leak_detective, detailed);
		lib->leak_detective->destroy(lib->leak_detective);
	}

	arrays_deinit();
	threads_deinit();
	backtrace_deinit();

	free((void*)this->public.ns);
	free(this);
	lib = NULL;
}
