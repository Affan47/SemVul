cavan_ext4_traversal_direct_indirect(struct cavan_ext4_walker *walker, u32 *blocks)
{
	int i;
	static const char steps[] = {12, 1, 1, 1};

	for (i = 0; i < NELEM(steps); i++)
	{
		int ret;

		ret = cavan_ext4_traversal_indirect(walker, blocks, steps[i], i);
		if (ret != WALKER_ACTION_CONTINUE)
		{
			return ret;
		}

		blocks += steps[i];
	}

	return 0;
}
