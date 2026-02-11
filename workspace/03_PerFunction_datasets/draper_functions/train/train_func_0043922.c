remove_pairs(GtkWidget *window, int flag_mask)
{
	struct gui_star_list *gsl;
	struct gui_star *gs;
	GSList *sl;

	gsl = gtk_object_get_data(GTK_OBJECT(window), "gui_star_list");
	if (gsl == NULL) {
		return;
	}
	sl = gsl->sl;
	while (sl != NULL) {
		gs = GUI_STAR(sl->data);
		sl = g_slist_next(sl);
		if ((gs->flags & (STAR_HAS_PAIR)) != (STAR_HAS_PAIR))
			continue;
		if (gs->pair != NULL
		    && ((gs->flags | gs->pair->flags) & flag_mask) == flag_mask) {
			remove_pair_from(gs);
		}
	}
	gtk_widget_queue_draw(window);
}
