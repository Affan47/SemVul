bookmark_get(struct view **view, position_t *cursor, position_t *mark,
		       unsigned id)
{
	struct bookmark *bm;
	for (bm = bookmarks; bm; bm = bm->next)
		if (bm->id == id) {
			*view = bm->view;
			*cursor = locus_get(bm->view, bm->locus[0]);
			if (*cursor == UNSET)
				*cursor = 0;
			*mark = locus_get(bm->view, bm->locus[1]);
			return TRUE;
		}
	*view = NULL;
	*cursor = *mark = 0;
	return FALSE;
}
