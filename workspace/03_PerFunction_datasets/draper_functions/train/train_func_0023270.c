find_name_by_ino(struct dir_context *ctx, const char *name, int namelen,
		 loff_t offset, u64 ino, unsigned int d_type)
{
	struct find_name_by_ino *a = container_of(ctx, struct find_name_by_ino,
						  ctx);

	a->called++;
	if (a->ino != ino)
		return 0;

	memcpy(a->name, name, namelen);
	a->namelen = namelen;
	a->found = 1;
	return 1;
}
