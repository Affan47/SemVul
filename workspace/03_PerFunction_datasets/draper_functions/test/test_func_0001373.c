_get_block(const char *path, void *block_list)
{
	char temp[PATH_MAX];
	char link[PATH_MAX];
	struct block_device *device = NULL;

	str_cpy(temp, path, PATH_MAX);
	str_cat(temp, "/block", PATH_MAX);

	if (realpath(temp, link))
		device = list_first_that(block_list, _compare, link);
	return device;
}
