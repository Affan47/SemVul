ccache(int argc, char *argv[])
{
	char now[64];
	time_t t;
	struct tm *tm;
	int put_object_in_manifest = 0;
	struct file_hash *object_hash_from_manifest = NULL;
	char *env;

	t = time(NULL);
	tm = localtime(&t);
	if (!tm) {
		cc_log("localtime failed");
		failed();
	}

	if (strftime(now, sizeof(now), "%Y-%m-%d %H:%M:%S", tm) == 0) {
		cc_log("strftime failed");
		failed();
	}

	cc_log("=== %s ===", now);

	cc_log("Base directory: %s", base_dir);


	find_compiler(argc, argv);


	if (!cache_dir) {
		cc_log("Unable to determine home directory");
		cc_log("ccache is disabled");
		failed();
	}


	if (getenv("CCACHE_DISABLE")) {
		cc_log("ccache is disabled");
		failed();
	}

	if (getenv("CCACHE_UNIFY")) {
		enable_unify = 1;
	}

	if (getenv("CCACHE_NODIRECT") || enable_unify) {
		cc_log("Direct mode disabled");
		enable_direct = 0;
	}

	if ((env = getenv("CCACHE_NLEVELS"))) {
		nlevels = atoi(env);
		if (nlevels < 1) nlevels = 1;
		if (nlevels > 8) nlevels = 8;
	}


	process_args(orig_args->argc, orig_args->argv);

	cc_log("Source file: %s", input_file);
	if (generating_dependencies) {
		cc_log("Dependency file: %s", output_dep);
	}
	cc_log("Object file: %s", output_obj);


	if (enable_direct) {
		if (find_hash(stripped_args, FINDHASH_DIRECT_MODE)) {


			from_cache(FROMCACHE_DIRECT_MODE, 0);


			put_object_in_manifest = 0;

			object_hash_from_manifest = object_hash;
			object_hash = NULL;
		} else {

			put_object_in_manifest = 1;
		}
	}


	find_hash(stripped_args, FINDHASH_CPP_MODE);

	if (object_hash_from_manifest
	    && !file_hashes_equal(object_hash_from_manifest, object_hash)) {


		cc_log("Hash from manifest doesn't match preprocessor output");
		cc_log("Likely reason: different CCACHE_BASEDIRs used");
		cc_log("Removing manifest as a safety measure");
		unlink(manifest_path);

		put_object_in_manifest = 1;
	}


	from_cache(FROMCACHE_CPP_MODE, put_object_in_manifest);

	if (getenv("CCACHE_READONLY")) {
		cc_log("Read-only mode; running real compiler");
		failed();
	}

	env = getenv("CCACHE_PREFIX");
	if (env) {
		char *p = find_executable(env, MYNAME);
		if (!p) {
			perror(env);
			exit(1);
		}
		cc_log("Using command-line prefix %s", env);
		args_add_prefix(stripped_args, p);
	}


	to_cache(stripped_args);


	from_cache(FROMCACHE_COMPILED_MODE, put_object_in_manifest);


	cc_log("Secondary from_cache failed");
	stats_update(STATS_ERROR);
	failed();
}
