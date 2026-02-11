qpol_is_file_mod_pkg(FILE * fp)
{
	size_t sz;
	__u32 ubuf;
	int rt;

	sz = fread(&ubuf, sizeof(__u32), 1, fp);

	if (sz != 1)
		rt = 0;

	ubuf = le32_to_cpu(ubuf);
	if (ubuf == SEPOL_MODULE_PACKAGE_MAGIC)
		rt = 1;
	else
		rt = 0;
	rewind(fp);
	return rt;
}
