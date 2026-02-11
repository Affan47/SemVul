data_structure_compatible(int structure_version, uint32_t latest_compatible,
	uint32_t current)
{
	if (structure_version >= latest_compatible && structure_version <= current) {
		return 1;
	}

	ast_log(LOG_ERROR, "A module is not compatible with the"
		"current data api version\n");

	return 0;
}
