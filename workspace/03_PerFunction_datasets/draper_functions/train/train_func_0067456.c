git_blob_set_rawcontent(git_blob *blob, const void *buffer, size_t len)
{
	assert(blob && buffer);

	blob->object.modified = 1;

	git_object__source_close((git_object *)blob);

	if (blob->content.data != NULL)
		gitfo_free_buf(&blob->content);

	blob->content.data = git__malloc(len);
	blob->content.len = len;

	if (blob->content.data == NULL)
		return GIT_ENOMEM;

	memcpy(blob->content.data, buffer, len);

	return GIT_SUCCESS;
}
