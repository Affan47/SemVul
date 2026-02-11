get_third_component(struct super_block *s,
				 const char *name, int len)
{
	__u32 res;

	if (!len || (len == 1 && name[0] == '.'))
		return DOT_OFFSET;
	if (len == 2 && name[0] == '.' && name[1] == '.')
		return DOT_DOT_OFFSET;

	res = REISERFS_SB(s)->s_hash_function(name, len);


	res = GET_HASH_VALUE(res);
	if (res == 0)


		res = 128;
	return res + MAX_GENERATION_NUMBER;
}
