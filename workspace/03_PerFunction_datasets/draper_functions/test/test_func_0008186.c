kmod_module_new_from_name(struct kmod_ctx *ctx,
						const char *name,
						struct kmod_module **mod)
{
	size_t namelen;
	char name_norm[PATH_MAX];

	if (ctx == NULL || name == NULL || mod == NULL)
		return -ENOENT;

	modname_normalize(name, name_norm, &namelen);

	return kmod_module_new(ctx, name_norm, name_norm, namelen, NULL, 0, mod);
}
