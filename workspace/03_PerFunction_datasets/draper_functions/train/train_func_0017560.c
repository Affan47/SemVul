e2fsck_allocate_context(e2fsck_t *ret)
{
	e2fsck_t	context;
	errcode_t	retval;
	char		*time_env;

	retval = ext2fs_get_mem(sizeof(struct e2fsck_struct), &context);
	if (retval)
		return retval;

	memset(context, 0, sizeof(struct e2fsck_struct));

	context->process_inode_size = 256;
	context->ext_attr_ver = 2;
	context->blocks_per_page = 1;
	context->htree_slack_percentage = 255;

	time_env = getenv("E2FSCK_TIME");
	if (time_env)
		context->now = strtoul(time_env, NULL, 0);
	else
		context->now = time(0);

	*ret = context;
	return 0;
}
