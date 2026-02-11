select_commit_parent_handler(void *data, char *buf, int c)
{
	size_t parents = *(size_t *) data;
	int parent = 0;

	if (!isdigit(c))
		return INPUT_SKIP;

	if (*buf)
		parent = atoi(buf) * 10;
	parent += c - '0';

	if (parent > parents)
		return INPUT_SKIP;
	return INPUT_OK;
}
