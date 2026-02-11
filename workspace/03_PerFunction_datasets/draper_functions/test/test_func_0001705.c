get_packed_refs(const char *submodule)
{
	const char *packed_refs_file;
	struct cached_refs *refs;

	if (submodule) {
		packed_refs_file = git_path_submodule(submodule, "packed-refs");
		refs = &submodule_refs;
		free_ref_list(refs->packed);
	} else {
		packed_refs_file = git_path("packed-refs");
		refs = &cached_refs;
	}

	if (!refs->did_packed || submodule) {
		FILE *f = fopen(packed_refs_file, "r");
		refs->packed = NULL;
		if (f) {
			read_packed_refs(f, refs);
			fclose(f);
		}
		refs->did_packed = 1;
	}
	return refs->packed;
}
