kmod_module_unref(struct kmod_module *mod)
{
	if (mod == NULL)
		return NULL;

	if (--mod->refcount > 0)
		return mod;

	DBG(mod->ctx, "kmod_module %p released\n", mod);

	kmod_pool_del_module(mod->ctx, mod, mod->hashkey);
	kmod_module_unref_list(mod->dep);

	if (mod->file)
		kmod_file_unref(mod->file);

	kmod_unref(mod->ctx);
	free(mod->options);
	free(mod->path);
	free(mod);
	return NULL;
}
