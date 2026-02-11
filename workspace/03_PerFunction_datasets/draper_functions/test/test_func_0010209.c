depmod_shutdown(struct depmod *depmod)
{
	size_t i;

	hash_free(depmod->symbols);

	hash_free(depmod->modules_by_relpath);

	hash_free(depmod->modules_by_name);

	for (i = 0; i < depmod->modules.count; i++)
		mod_free(depmod->modules.array[i]);
	array_free_array(&depmod->modules);

	kmod_unref(depmod->ctx);
}
