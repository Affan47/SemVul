kmod_module_apply_filter(const struct kmod_ctx *ctx,
						enum kmod_filter filter_type,
						const struct kmod_list *input,
						struct kmod_list **output)
{
	const struct kmod_list *li;

	if (ctx == NULL || output == NULL)
		return -ENOENT;

	*output = NULL;
	if (input == NULL)
		return 0;

	kmod_list_foreach(li, input) {
		struct kmod_module *mod = li->data;
		struct kmod_list *node;

		if ((filter_type & KMOD_FILTER_BLACKLIST) &&
				module_is_blacklisted(mod))
			continue;

		if ((filter_type & KMOD_FILTER_BUILTIN) && mod->builtin)
			continue;

		node = kmod_list_append(*output, mod);
		if (node == NULL)
			goto fail;

		*output = node;
		kmod_module_ref(mod);
	}

	return 0;

fail:
	kmod_module_unref_list(*output);
	*output = NULL;
	return -ENOMEM;
}
