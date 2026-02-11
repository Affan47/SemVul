cli_chm_extract_file(char *dirname, chm_metadata_t *metadata, cli_ctx *ctx)
{
	char filename[1024];
	uint64_t len;

	cli_dbgmsg("in cli_chm_extract_file\n");

	if (lseek(metadata->ufd, metadata->file_offset, SEEK_SET) != (off_t) metadata->file_offset) {
		cli_dbgmsg("seek in uncompressed stream failed\n");
		return CL_EFORMAT;
	}
	snprintf(filename, 1024, "%s"PATHSEP"%lu.chm", dirname, (unsigned long int) metadata->file_offset);
	metadata->ofd = open(filename, O_RDWR|O_CREAT|O_TRUNC|O_BINARY, S_IRWXU);
	if (metadata->ofd < 0) {
		return CL_ECREAT;
	}
	len = ctx->engine->maxfilesize ? (MIN(ctx->engine->maxfilesize, metadata->file_length)) : metadata->file_length;
	if (chm_copy_file_data(metadata->ufd, metadata->ofd, len) != len) {
		cli_dbgmsg("failed to copy %lu bytes\n", (unsigned long int) len);
		close(metadata->ofd);
		return CL_EFORMAT;
	}

	return CL_SUCCESS;
}
