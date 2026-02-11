chirp_multi_statfs(const char *volume, const char *path, struct chirp_statfs * buf, time_t stoptime)
{
	struct chirp_server *s;
	INT64_T files_total = 0;
	INT64_T bytes_avail = 0;
	INT64_T bytes_free = 0;
	INT64_T bytes_total = 0;
	INT64_T files_free = 0;
	INT64_T block_size = 4096;
	int i;

	if(!chirp_multi_init(volume, stoptime))
		return 0;

	for(i = 0; i < current_volume->nservers; i++) {
		s = current_volume->servers[i];
		struct chirp_statfs tmp;
		int result;

		result = chirp_reli_statfs(s->name, "/", &tmp, stoptime);
		if(result < 0)
			return result;

		bytes_total += tmp.f_blocks * (INT64_T) tmp.f_bsize;
		bytes_avail += tmp.f_bavail * (INT64_T) tmp.f_bsize;
		bytes_free += tmp.f_bfree * (INT64_T) tmp.f_bsize;
		files_total += tmp.f_files;
		files_free += tmp.f_ffree;
	}

	memset(buf, 0, sizeof(*buf));

	buf->f_bsize = block_size;
	buf->f_blocks = bytes_total / block_size;
	buf->f_bavail = bytes_avail / block_size;
	buf->f_bfree = bytes_free / block_size;
	buf->f_files = files_total;
	buf->f_ffree = files_total;

	return 0;
}
