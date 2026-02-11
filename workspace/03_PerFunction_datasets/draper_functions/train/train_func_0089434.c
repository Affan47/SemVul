chirp_multi_getdir(const char *volume, const char *path, chirp_dir_t callback, void *arg, time_t stoptime)
{
	char lpath[CHIRP_PATH_MAX];
	if(!volume[0]) {
		callback(".", arg);
		callback("..", arg);
		return 0;
	} else if(!chirp_multi_lpath(volume, path, lpath, stoptime)) {
		return -1;
	} else {
		return chirp_reli_getdir(current_volume->host, lpath, callback, arg, stoptime);
	}
}
