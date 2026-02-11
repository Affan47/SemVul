frozen_free(struct hashdir *hd)
{
	frozen_list_del(hd->frozen_list, hd);
	free(hd->dirtyname);
	if (hd->bitmap) {
		bitmap_free(hd->bitmap);
	}
	free(hd->deleted);
}
