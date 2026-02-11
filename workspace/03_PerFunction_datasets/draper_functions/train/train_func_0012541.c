git_diff_blobs(
	const git_blob *old_blob,
	const git_blob *new_blob,
	const git_diff_options *options,
	git_diff_file_cb file_cb,
	git_diff_hunk_cb hunk_cb,
	git_diff_data_cb data_cb,
	void *payload)
{
	int error;
	diff_single_data d;
	git_repository *repo =
		new_blob ? git_object_owner((const git_object *)new_blob) :
		old_blob ? git_object_owner((const git_object *)old_blob) : NULL;

	if (!repo)
		return 0;

	if ((error = diff_single_init(
			&d, repo, options, file_cb, hunk_cb, data_cb, payload)) < 0)
		return error;

	if (options && (options->flags & GIT_DIFF_REVERSE) != 0) {
		const git_blob *swap = old_blob;
		old_blob = new_blob;
		new_blob = swap;
	}

	set_data_from_blob(old_blob, &d.patch.old_data, &d.delta.old_file);
	set_data_from_blob(new_blob, &d.patch.new_data, &d.delta.new_file);

	return diff_single_apply(&d);
}
