git_pack_config(const char *k, const char *v, void *cb)
{
	if (!strcmp(k, "pack.depth")) {
		max_depth = git_config_int(k, v);
		if (max_depth > MAX_DEPTH)
			max_depth = MAX_DEPTH;
		return 0;
	}
	if (!strcmp(k, "pack.compression")) {
		int level = git_config_int(k, v);
		if (level == -1)
			level = Z_DEFAULT_COMPRESSION;
		else if (level < 0 || level > Z_BEST_COMPRESSION)
			die("bad pack compression level %d", level);
		pack_compression_level = level;
		pack_compression_seen = 1;
		return 0;
	}
	if (!strcmp(k, "pack.indexversion")) {
		pack_idx_default_version = git_config_int(k, v);
		if (pack_idx_default_version > 2)
			die("bad pack.indexversion=%"PRIu32,
			    pack_idx_default_version);
		return 0;
	}
	if (!strcmp(k, "pack.packsizelimit")) {
		max_packsize = git_config_ulong(k, v);
		return 0;
	}
	if (!strcmp(k, "core.bigfilethreshold")) {
		long n = git_config_int(k, v);
		big_file_threshold = 0 < n ? n : 0;
	}
	return git_default_config(k, v, cb);
}
