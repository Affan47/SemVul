string_copy(e2fsck_t ctx EXT2FS_ATTR((unused)),
		  const char *str, int len)
{
	char	*ret;

	if (!str)
		return NULL;
	if (!len)
		len = strlen(str);
	ret = malloc(len+1);
	if (ret) {
		strncpy(ret, str, len);
		ret[len] = 0;
	}
	return ret;
}
