Resize(int width, int height) {


#if GTK_CHECK_VERSION(3,0,0)
	GtkRequisition requisition;
	gtk_widget_get_requisition(PWidget(scrollbarv), &requisition);
	scrollBarWidth = requisition.width;
	gtk_widget_get_requisition(PWidget(scrollbarh), &requisition);
	scrollBarHeight = requisition.height;
#else
	scrollBarWidth = GTK_WIDGET(PWidget(scrollbarv))->requisition.width;
	scrollBarHeight = GTK_WIDGET(PWidget(scrollbarh))->requisition.height;
#endif


	bool showSBHorizontal = horizontalScrollBarVisible && (wrapState == eWrapNone);
	int horizontalScrollBarHeight = scrollBarHeight;
	if (!showSBHorizontal)
		horizontalScrollBarHeight = 0;

	GtkAllocation alloc;
	if (showSBHorizontal) {
		gtk_widget_show(GTK_WIDGET(PWidget(scrollbarh)));
		alloc.x = 0;
		alloc.y = height - scrollBarHeight;
		alloc.width = Platform::Maximum(1, width - scrollBarWidth);
		alloc.height = horizontalScrollBarHeight;
		gtk_widget_size_allocate(GTK_WIDGET(PWidget(scrollbarh)), &alloc);
	} else {
		gtk_widget_hide(GTK_WIDGET(PWidget(scrollbarh)));
	}

	if (verticalScrollBarVisible) {
		gtk_widget_show(GTK_WIDGET(PWidget(scrollbarv)));
		alloc.x = width - scrollBarWidth;
		alloc.y = 0;
		alloc.width = scrollBarWidth;
		alloc.height = Platform::Maximum(1, height - scrollBarHeight);
		if (!showSBHorizontal)
			alloc.height += scrollBarWidth-1;
		gtk_widget_size_allocate(GTK_WIDGET(PWidget(scrollbarv)), &alloc);
	} else {
		gtk_widget_hide(GTK_WIDGET(PWidget(scrollbarv)));
	}
	if (IS_WIDGET_MAPPED(PWidget(wMain))) {
		ChangeSize();
	}

	alloc.x = 0;
	alloc.y = 0;
	alloc.width = Platform::Maximum(1, width - scrollBarWidth);
	alloc.height = Platform::Maximum(1, height - scrollBarHeight);
	if (!showSBHorizontal)
		alloc.height += scrollBarHeight;
	if (!verticalScrollBarVisible)
		alloc.width += scrollBarWidth;
	gtk_widget_size_allocate(GTK_WIDGET(PWidget(wText)), &alloc);
}
