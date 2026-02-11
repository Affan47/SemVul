chirp_reli_flistxattr(struct chirp_file *file, char *list, size_t size, time_t stoptime)
{
	chirp_reli_flush(file,stoptime);
	RETRY_FILE( result = chirp_client_flistxattr(client,file->fd,list,size,stoptime); )
}
