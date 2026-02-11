chirp_multi_create(const char *volume, const char *path, INT64_T flags, INT64_T mode, time_t stoptime)
{
	struct chirp_server *server;
	struct file_info info;

	if(!chirp_multi_lpath(volume, path, info.lpath, stoptime))
		return 0;

	while(1) {
		server = chirp_volume_server_choose(current_volume);
		if(!server) {
			errno = ENOSPC;
			return 0;
		}

		if(!server->prepared) {
			debug(D_MULTI, "preparing server %s", server->name);
			char keypath[CHIRP_PATH_MAX];
			sprintf(keypath, "/%s", current_volume->key);
			int result = chirp_reli_mkdir_recursive(server->name, keypath, 0777, stoptime);
			if(result < 0 && errno != EEXIST) {
				server->priority += 10;
				continue;
			}
			server->prepared = 1;
		}

		char cookie[17];
		strcpy(info.rhost, server->name);
		string_cookie(cookie, 16);
		sprintf(info.rpath, "%s/%s", current_volume->key, cookie);

		debug(D_MULTI, "create: /multi/%s%s at /chirp/%s/%s", volume, path, info.rhost, info.rpath);
		if(chirp_multi_update(volume, path, &info, stoptime) < 0)
			return 0;


		struct chirp_file *file = chirp_reli_open(info.rhost, info.rpath, flags | O_EXCL, mode, stoptime);
		if(file) {
			server->priority += 1;
			return file;
		} else {
			debug(D_MULTI, "create failed, trying another server...");
			server->priority += 10;
		}
	}


}
