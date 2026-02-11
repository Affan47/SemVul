git_blob_set_rawcontent_fromfile(git_blob *blob, const char *filename)
{
	assert(blob && filename);
	blob->object.modified = 1;

	if (blob->content.data != NULL)
		gitfo_free_buf(&blob->content);

	return gitfo_read_file(&blob->content, filename);
}
