merge_star(GList *csl, struct cat_star *new)
{
	GList *sl;
	struct cat_star *cats;

	for (sl = csl; sl != NULL; sl = sl->next) {
		cats = CAT_STAR(sl->data);
		if (cats_is_duplicate(cats, new)) {

			if (CATS_TYPE(cats) == CAT_STAR_TYPE_SREF) {
				cat_star_release(cats);
				cat_star_ref(new);
				sl->data = new;
			} else if (CATS_TYPE(cats) == CAT_STAR_TYPE_ALIGN) {
				if (CATS_TYPE(new) != CAT_STAR_TYPE_SREF) {
					cat_star_release(cats);
					cat_star_ref(new);
					sl->data = new;
				}
			} else if (CATS_TYPE(cats) == CAT_STAR_TYPE_CAT) {
				if (CATS_TYPE(new) != CAT_STAR_TYPE_SREF
				    && CATS_TYPE(new) != CAT_STAR_TYPE_ALIGN) {
					cat_star_release(cats);
					cat_star_ref(new);
					sl->data = new;
				}
			} else if (CATS_TYPE(cats) == CAT_STAR_TYPE_APSTD
				   || CATS_TYPE(cats) == CAT_STAR_TYPE_APSTAR) {
				if (CATS_TYPE(new) == CAT_STAR_TYPE_APSTD
				    || CATS_TYPE(new) == CAT_STAR_TYPE_APSTAR) {
					cat_star_release(cats);
					cat_star_ref(new);
					sl->data = new;
				}
			}
			break;
		}
	}
	if (sl == NULL) {
		cat_star_ref(new);
		csl = g_list_prepend(csl, new);
	}
	return csl;
}
