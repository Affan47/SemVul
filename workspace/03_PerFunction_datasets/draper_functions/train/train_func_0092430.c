truncate_pack(off_t to, git_SHA_CTX *ctx)
{
	if (ftruncate(pack_data->pack_fd, to)
	 || lseek(pack_data->pack_fd, to, SEEK_SET) != to)
		die_errno("cannot truncate pack to skip duplicate");
	pack_size = to;


	pack_file->total = to;
	pack_file->offset = 0;
	pack_file->ctx = *ctx;
}
