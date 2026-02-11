write_extension(git_filebuf *file, struct index_extension *header, git_buf *data)
{
	struct index_extension ondisk;
	int error = 0;

	memset(&ondisk, 0x0, sizeof(struct index_extension));
	memcpy(&ondisk, header, 4);
	ondisk.extension_size = htonl(header->extension_size);

	if ((error = git_filebuf_write(file, &ondisk, sizeof(struct index_extension))) == 0)
		error = git_filebuf_write(file, data->ptr, data->size);

	return error;
}
