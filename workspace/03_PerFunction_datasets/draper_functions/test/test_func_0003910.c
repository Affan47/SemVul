runtime_strequal(bool *eq, uintptr s, void *a, void *b)
{
	int32 alen;

	alen = ((String*)a)->len;
	if(alen != ((String*)b)->len) {
		*eq = false;
		return;
	}
	runtime_memequal(eq, alen, ((String*)a)->str, ((String*)b)->str);
}
