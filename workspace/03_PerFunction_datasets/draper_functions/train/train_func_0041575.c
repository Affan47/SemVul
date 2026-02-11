chirp_global_statfs(const char *host, const char *path, struct chirp_statfs * buf, time_t stoptime)
{
	if(is_multi_path(host)) {
		char mhost[CHIRP_PATH_MAX];
		char mpath[CHIRP_PATH_MAX];
		parse_multi_path(path, mhost, mpath);
		return chirp_multi_statfs(mhost, mpath, buf, stoptime);
	} else if(not_empty(path)) {
		return chirp_reli_statfs(host, path, buf, stoptime);
	} else if(not_empty(host)) {
		return chirp_reli_statfs(host, "/", buf, stoptime);
	} else {
		memset(buf, 0, sizeof(*buf));
		return 0;
	}

}
