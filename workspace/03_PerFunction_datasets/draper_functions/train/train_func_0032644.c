awe_make_unique_name(char *given, FILE *fp, char *dst)
{
	struct stat st;

	if (fstat(fileno(fp), &st) < 0) {
		if (awe_verbose)
			fprintf(stderr, "parsesf: can't get stat of font file\n");
		return AWE_RET_ERR;
	}

	dst[0] = ASC_TO_KEY('A');
	dst[1] = ASC_TO_KEY('W');
	dst[2] = ASC_TO_KEY('E');
	dst[3] = 0x00;
	dst[4] = 0x04;
	dst[5] = 0x03;
	sprintf(dst + 6, "%-18.18s", given);

	*(int*)(dst + 24) = (int)st.st_mtime;
	*(int*)(dst + 28) = (int)st.st_size;

	return AWE_RET_OK;
}
