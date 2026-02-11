qupdate(void *ign)
{
	int wait;
	int x;
	struct gui_queue *obj;
	char swait[40];
	time_t now;
	time(&now);
	for (x=0;x<GTK_CLIST(qlist)->rows;x++) {
		obj = gtk_clist_get_row_data(GTK_CLIST(qlist), x);
		if (obj->type == TYPE_QUEUE) {
			wait = now - obj->base + obj->offset;
			if (wait > 3600)
				snprintf(swait, sizeof(swait), "%d:%02d:%02d", wait/3600, (wait % 3600) / 60, wait % 60);
			else
				snprintf(swait, sizeof(swait), "%d:%02d", wait / 60, wait % 60);
			gtk_clist_set_text(GTK_CLIST(qlist), x, 4, swait);
		}
	}
	return 1;
}
