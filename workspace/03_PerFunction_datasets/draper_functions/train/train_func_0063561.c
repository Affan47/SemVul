StartDrag() {
	PLATFORM_ASSERT(evbtn != 0);
	dragWasDropped = false;
	inDragDrop = ddDragging;
	GtkTargetList *tl = gtk_target_list_new(clipboardCopyTargets, nClipboardCopyTargets);
	gtk_drag_begin(GTK_WIDGET(PWidget(wMain)),
	               tl,
	               static_cast<GdkDragAction>(GDK_ACTION_COPY | GDK_ACTION_MOVE),
	               evbtn->button,
	               reinterpret_cast<GdkEvent *>(evbtn));
}
