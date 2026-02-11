techroom_intel_init()
{
	int rval, temp;
	static int inited = 0;

	if (inited)
		return;


	lcl_ext_open();

	if ((rval = setjmp(parse_abort)) != 0) {
		mprintf(("TABLES: Unable to parse '%s'!  Error code = %i.\n", "species.tbl", rval));
		lcl_ext_close();
		return;
	}

	read_file_text("species.tbl", CF_TYPE_TABLES);
	reset_parse();

	Intel_info_size = 0;
	while (optional_string("$Entry:")) {
		Assert(Intel_info_size < MAX_INTEL_ENTRIES);
		if (Intel_info_size >= MAX_INTEL_ENTRIES) {
			mprintf(("TECHMENU: Too many intel entries!\n"));
			break;
		}

		Intel_info[Intel_info_size].flags = IIF_DEFAULT_VALUE;

		required_string("$Name:");
		stuff_string(Intel_info[Intel_info_size].name, F_NAME, NAME_LENGTH);

		required_string("$Anim:");
		stuff_string(Intel_info[Intel_info_size].anim_filename, F_NAME, NAME_LENGTH);

		required_string("$AlwaysInTechRoom:");
		stuff_int(&temp);
		if (temp) {

			Intel_info[Intel_info_size].flags |= IIF_IN_TECH_DATABASE;
			Intel_info[Intel_info_size].flags |= IIF_DEFAULT_IN_TECH_DATABASE;
		}

		required_string("$Description:");
		stuff_string(Intel_info[Intel_info_size].desc, F_MULTITEXT, TECH_INTEL_DESC_LEN);

		Intel_info_size++;
	}

	inited = 1;


	lcl_ext_close();
}
