gfs_server_pwrite(struct gfp_xdr *client)
{
	gfarm_int32_t fd;
	size_t size;
	gfarm_int64_t offset;
	ssize_t rv;
	int save_errno = 0;
	char buffer[GFS_PROTO_MAX_IOSIZE];

	gfs_server_get_request(client, "pwrite", "ibl",
	    &fd, sizeof(buffer), &size, buffer, &offset);


	if (size > GFS_PROTO_MAX_IOSIZE)
		size = GFS_PROTO_MAX_IOSIZE;
#if 0
	if ((rv = pwrite(file_table_get(fd), buffer, size, offset)) == -1)
#else
	rv = 0;
	if (lseek(file_table_get(fd), offset, SEEK_SET) == -1)
		save_errno = errno;
	else if ((rv = write(file_table_get(fd), buffer, size)) == -1)
#endif
		save_errno = errno;
	else
		file_table_set_written(fd);

	gfs_server_put_reply_with_errno(client, "pwrite", save_errno,
	    "i", (gfarm_int32_t)rv);
}
