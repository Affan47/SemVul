FILE_openNULL(CTX ctx, kPath *path, const char *mode, kDictMap *conf)
{
	FILE *fp = fopen(path->ospath, mode);
	if(fp != NULL) return new_FILE(ctx, fp, 4096);
	return NULL;
}
