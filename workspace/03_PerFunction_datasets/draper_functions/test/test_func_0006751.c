free_alignment_stars(struct ccd_reduce *ccdr)
{
	GSList *as = NULL;

	as = ccdr->align_stars;
	while (as != NULL) {
		gui_star_release(GUI_STAR(as->data));
		as = g_slist_next(as);
	}
	g_slist_free(ccdr->align_stars);
	ccdr->align_stars = NULL;
	ccdr->ops &= ~CCDR_ALIGN_STARS;
}
