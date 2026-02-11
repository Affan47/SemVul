str_read(char **strp, gfp_t flags, void *fp, u32 len)
{
	int rc;
	char *str;

	str = kmalloc(len + 1, flags);
	if (!str)
		return -ENOMEM;


	*strp = str;

	rc = next_entry(str, fp, len);
	if (rc)
		return rc;

	str[len] = '\0';
	return 0;
}
