stuff_and_malloc_string(int type, char *terminators)
{
	SCP_string tmp_result;

	stuff_string(tmp_result, type, terminators);
	drop_white_space(tmp_result);

	if (tmp_result.empty())
		return NULL;

	return vm_strdup(tmp_result.c_str());
}
