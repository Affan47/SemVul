stf_keep_good_phot(struct stf *stf)
{
	GList *sl, *nsl=NULL;
	struct stf *st;
	struct cat_star *cats;

	st = stf_find(stf, 0, SYM_STARS);
	if (st == NULL || st->next == NULL || !STF_IS_GLIST(st->next))
		return;
	sl = STF_GLIST(st->next);
	for (; sl != NULL; sl = sl->next) {
		cats = CAT_STAR(sl->data);
		if (CATS_TYPE(cats) != CAT_STAR_TYPE_APSTAR &&
		    CATS_TYPE(cats) != CAT_STAR_TYPE_APSTD) {
			cat_star_release(cats);
			continue;
		}
		if (cats->flags & CPHOT_INVALID) {
			cat_star_release(cats);
			continue;
		}
		if ((CATS_TYPE(cats) == CAT_STAR_TYPE_APSTD) &&
		    (cats->flags & CPHOT_NOT_FOUND) &&
		    P_INT(AP_DISCARD_UNLOCATED)) {
			cat_star_release(cats);
			continue;
		}
		nsl = g_list_prepend(nsl, cat_star_dup(cats));
		cat_star_release(cats);
	}
	g_list_free(STF_GLIST(st->next));
	STF_SET_GLIST(st->next, nsl);
}
