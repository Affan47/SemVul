gnm_notebook_size_allocate (GtkWidget     *widget,
			    GtkAllocation *allocation)
{
	int i, h = 0;
	GnmNotebook *gnb = (GnmNotebook *)widget;
	GtkAllocation alc = *allocation;

	for (i = 0; TRUE; i++) {
		GtkWidget *page = gtk_notebook_get_nth_page (GTK_NOTEBOOK (widget), i);
		GtkAllocation a;
		if (!page)
			break;
		if (!gtk_widget_get_visible (page))
			continue;
		gtk_widget_get_allocation (page, &a);
		h = MAX (h, a.height);
	}

	gnb->dummy_height = h;

	alc.y -= h;
	((GtkWidgetClass *)gnm_notebook_parent_class)->size_allocate
		(widget, &alc);
}
