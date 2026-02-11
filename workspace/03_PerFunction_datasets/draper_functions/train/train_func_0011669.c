gui_stars_selection(struct gui_star_list *gsl, int type_mask)
{
	GSList *ret_sl = NULL;
	GSList *sl;
	struct gui_star * gs;

	sl = gsl->sl;
	while (sl != NULL) {
		gs = GUI_STAR(sl->data);
		sl = g_slist_next(sl);
		if (!(TYPE_MASK_GSTAR(gs) & gsl->display_mask))
			continue;
		if (type_mask) {
			if (!(TYPE_MASK_GSTAR(gs) & type_mask))
				continue;
		} else {
			if (!(TYPE_MASK_GSTAR(gs) & gsl->select_mask))
				continue;
		}
		if (gs->flags & STAR_SELECTED) {
			ret_sl = g_slist_prepend(ret_sl, gs);
		}
	}
	return ret_sl;
}
