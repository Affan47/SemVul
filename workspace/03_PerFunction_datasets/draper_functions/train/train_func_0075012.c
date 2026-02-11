chirp_global_removexattr(const char *host, const char *path, const char *name, time_t stoptime)
{
	if(is_multi_path(host)) {
		errno = EACCES;
		return -1;
	} else if(not_empty(path)) {
		return chirp_reli_removexattr(host, path, name, stoptime);
	} else if(not_empty(host)) {
		if(server_lookup(host, stoptime)) {
			errno = EACCES;
			return -1;
		} else {
			errno = ENOENT;
			return -1;
		}
	} else {
		errno = EACCES;
		return -1;
	}
}
