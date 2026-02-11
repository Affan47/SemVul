gf_isom_set_copyright(GF_ISOFile *movie, const char *threeCharCode, char *notice)
{
	GF_Err e;
	GF_CopyrightBox *ptr;
	GF_UserDataMap *map;
	u32 count, i;

	e = CanAccessMovie(movie, GF_ISOM_OPEN_WRITE);
	if (e) return e;

	if (!notice || !threeCharCode) return GF_BAD_PARAM;

	gf_isom_insert_moov(movie);

	if (!movie->moov->udta) {
		e = moov_AddBox((GF_Box*)movie->moov, gf_isom_box_new(GF_ISOM_BOX_TYPE_UDTA));
		if (e) return e;
	}
	map = udta_getEntry(movie->moov->udta, GF_ISOM_BOX_TYPE_CPRT, NULL);

	if (map) {

		count = gf_list_count(map->other_boxes);
		for (i=0; i<count; i++) {
			ptr = (GF_CopyrightBox*)gf_list_get(map->other_boxes, i);
			if (!strcmp(threeCharCode, (const char *) ptr->packedLanguageCode)) {
				gf_free(ptr->notice);
				ptr->notice = (char*)gf_malloc(sizeof(char) * (strlen(notice) + 1));
				strcpy(ptr->notice, notice);
				return GF_OK;
			}
		}
	}

	ptr = (GF_CopyrightBox *)gf_isom_box_new(GF_ISOM_BOX_TYPE_CPRT);

	memcpy(ptr->packedLanguageCode, threeCharCode, 4);
	ptr->notice = (char*)gf_malloc(sizeof(char) * (strlen(notice)+1));
	strcpy(ptr->notice, notice);
	return udta_AddBox(movie->moov->udta, (GF_Box *) ptr);
}
