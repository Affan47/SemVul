detect_versions(sci_version_t *version, int *res_version, cl_options_t *options, config_entry_t *conf)
{
	sci_version_t exe_version;
	sci_version_t hash_version;
	int hash_res_version;
	guint32 code;
	int got_exe_version;
	const char *game_name;

	sciprintf("Detecting interpreter and resource versions...\n");

	got_exe_version = !version_detect_from_executable(&exe_version);

	if (got_exe_version) {
		sciprintf("Interpreter version: %d.%03d.%03d (by executable scan)\n",
				  SCI_VERSION_MAJOR(exe_version),
				  SCI_VERSION_MINOR(exe_version),
				  SCI_VERSION_PATCHLEVEL(exe_version));

		if (SCI_VERSION_MAJOR(exe_version) >= 1) {
			sciprintf("FIXME: Implement version mapping (results of executable scan ignored)\n");
			got_exe_version = 0;
		}

	}

	game_name = version_guess_from_hashcode(&hash_version, &hash_res_version, &code);

	if (game_name) {
		sciprintf("Interpreter version: %d.%03d.%03d (by hash code %08X)\n",
				  SCI_VERSION_MAJOR(hash_version),
				  SCI_VERSION_MINOR(hash_version),
				  SCI_VERSION_PATCHLEVEL(hash_version), code);
		if (got_exe_version && exe_version != hash_version)
				sciprintf("UNEXPECTED INCONSISTENCY: Hash code %08X indicates interpreter version\n"
					  "  %d.%03d.%03d, but analysis of the executable yields %d.%03d.%03d (for game\n"
					  "  '%s'). Please report this!\n",
					  code,
					  SCI_VERSION_MAJOR(hash_version),
					  SCI_VERSION_MINOR(hash_version),
					  SCI_VERSION_PATCHLEVEL(hash_version),
					  SCI_VERSION_MAJOR(exe_version),
					  SCI_VERSION_MINOR(exe_version),
					  SCI_VERSION_PATCHLEVEL(exe_version), game_name);

		if (hash_res_version != SCI_VERSION_AUTODETECT)
			sciprintf("Resource version: %d (by hash code)\n", hash_res_version);

		sciprintf("Game identified as '%s'\n", game_name);
	} else {
		sciprintf("Could not identify game by hash code: %08X\n", code);

		if (got_exe_version)
			  sciprintf("Please report the preceding two lines and the name of the game you were trying\n"
			  	    "to run to the FreeSCI development team to help other users!\n",
			  code);
	}

	if (options->version)
		*version = options->version;
	else if (conf && conf->version)
		*version = conf->version;
	else if (game_name)
		*version = hash_version;
	else if (got_exe_version)
		*version = exe_version;
	else
		*version = 0;

	if (options->res_version != SCI_VERSION_AUTODETECT)
		*res_version = options->res_version;
	else if (conf && conf->res_version != SCI_VERSION_AUTODETECT)
		*res_version = conf->res_version;
	else if (game_name)
		*res_version = hash_res_version;
	else
		*res_version = SCI_VERSION_AUTODETECT;

	if (*version)
		sciprintf("Using interpreter version %d.%03d.%03d\n",
				  SCI_VERSION_MAJOR(*version),
				  SCI_VERSION_MINOR(*version),
				  SCI_VERSION_PATCHLEVEL(*version));

	if (*res_version != SCI_VERSION_AUTODETECT)
		sciprintf("Using resource version %d\n", *res_version);
}
