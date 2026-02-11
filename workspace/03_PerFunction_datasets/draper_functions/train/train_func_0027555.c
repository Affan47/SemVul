zWriteGTFConvInfo(FILE* stream, const zGTFConvInfo *conv) {
	char   gtf_type[32];
	int    i;

	for (i = 0; i < conv->maxStrIdx; ++i) {
		if (conv->strIdx2gtft[i] != zGTF_UNDEF) {
			zGTF2Text(conv->strIdx2gtft[i], gtf_type);
			fprintf(stream, "%s => %s\n", zStrIdx2Char(i), gtf_type);
		}
	}
}
