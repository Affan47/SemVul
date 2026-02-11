rhash_file(unsigned hash_id, const char* filepath, unsigned char* result)
{
	FILE* fd;
	rhash ctx;
	int res;

	hash_id &= RHASH_ALL_HASHES;
	if(hash_id == 0) return -1;

	if((fd = fopen(filepath, "rb")) == NULL) return -1;

	if((ctx = rhash_init(hash_id)) == NULL) return -1;

	res = rhash_file_update(ctx, fd);
	fclose(fd);

	rhash_final(ctx, result);
	rhash_free(ctx);
	return res;
}
