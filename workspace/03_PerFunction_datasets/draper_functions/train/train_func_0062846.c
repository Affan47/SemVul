apply_binary(struct buffer_desc *desc, struct patch *patch)
{
	const char *name = patch->old_name ? patch->old_name : patch->new_name;
	unsigned char sha1[20];


	if (strlen(patch->old_sha1_prefix) != 40 ||
	    strlen(patch->new_sha1_prefix) != 40 ||
	    get_sha1_hex(patch->old_sha1_prefix, sha1) ||
	    get_sha1_hex(patch->new_sha1_prefix, sha1))
		return error("cannot apply binary patch to '%s' "
			     "without full index line", name);

	if (patch->old_name) {


		hash_sha1_file(desc->buffer, desc->size, blob_type, sha1);
		if (strcmp(sha1_to_hex(sha1), patch->old_sha1_prefix))
			return error("the patch applies to '%s' (%s), "
				     "which does not match the "
				     "current contents.",
				     name, sha1_to_hex(sha1));
	}
	else {

		if (desc->size)
			return error("the patch applies to an empty "
				     "'%s' but it is not empty", name);
	}

	get_sha1_hex(patch->new_sha1_prefix, sha1);
	if (is_null_sha1(sha1)) {
		free(desc->buffer);
		desc->alloc = desc->size = 0;
		desc->buffer = NULL;
		return 0;
	}

	if (has_sha1_file(sha1)) {

		enum object_type type;
		unsigned long size;

		free(desc->buffer);
		desc->buffer = read_sha1_file(sha1, &type, &size);
		if (!desc->buffer)
			return error("the necessary postimage %s for "
				     "'%s' cannot be read",
				     patch->new_sha1_prefix, name);
		desc->alloc = desc->size = size;
	}
	else {


		if (apply_binary_fragment(desc, patch))
			return error("binary patch does not apply to '%s'",
				     name);


		hash_sha1_file(desc->buffer, desc->size, blob_type, sha1);
		if (strcmp(sha1_to_hex(sha1), patch->new_sha1_prefix))
			return error("binary patch to '%s' creates incorrect result (expecting %s, got %s)", name, patch->new_sha1_prefix, sha1_to_hex(sha1));
	}

	return 0;
}
