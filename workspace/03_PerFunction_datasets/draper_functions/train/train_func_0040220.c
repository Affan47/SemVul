list_store_append_mouse(P_Controls *page, const CtrlMouse *mouse, GtkTreeIter *iter)
{
	gchar   	*bname[] = { N_("Left"), N_("Middle"), N_("Right"), N_("Wheel Up"), N_("Wheel Down") };
	guint		btn;
	GtkTreeIter	myiter;


	if(iter == NULL)
		iter = &myiter;
	gtk_list_store_append(page->mstore, iter);
	btn = ctrl_mouse_get_button(mouse) - 1;
	gtk_list_store_set(page->mstore, iter,
			MOUSE_COLUMN_ICON,   page->mpbuf[btn],
			MOUSE_COLUMN_BUTTON, _(bname[btn]),
			MOUSE_COLUMN_STATE,  gtk_accelerator_name(0U, ctrl_mouse_get_state(mouse)),
			MOUSE_COLUMN_CMDSEQ, ctrl_mouse_get_cmdseq(mouse),
			MOUSE_COLUMN_MOUSE,  mouse,
			-1);
}
