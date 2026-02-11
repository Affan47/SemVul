__fru_alloc_get_tl(struct fru_common_header *header, int nr)
{
	struct fru_type_length *tl;
	char *res;
	int len;

	tl = __fru_get_board_tl(header, nr);
	if (!tl)
		return NULL;
	len = fru_strlen(tl);
	res = fru_alloc(fru_strlen(tl) + 1);
	if (!res)
		return NULL;
	return fru_strcpy(res, tl);
}
