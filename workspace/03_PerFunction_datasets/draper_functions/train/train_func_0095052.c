namepart(unsigned char *tmp, unsigned char *path)
{
	unsigned char *z;

	skip_drive_letter(path);
	z = path + zlen(path);
	while ((z != path) && (z[-1] != '/'))
		--z;
	return zcpy(tmp, z);
}
