dialog_cell_format (WBCGtk *wbcg, FormatDialogPosition_t pageno, gint pages)
{
	FormatState  *state;

	g_return_if_fail (wbcg != NULL);

	state = dialog_cell_format_init (wbcg);

        if (state == NULL)
                return;

	state->style_selector.is_selector = FALSE;
	state->style_selector.w = NULL;
	state->style_selector.closure = NULL;

	if (pages == 0) {
		int i;
		for (i = FD_NUMBER; i <= FD_PROTECTION; i++)
			pages |= (1 << i);
	}

	fmt_dialog_impl (state, pageno, pages);

	wbc_gtk_attach_guru (state->wbcg, GTK_WIDGET (state->dialog));
	go_gtk_nonmodal_dialog (wbcg_toplevel (state->wbcg),
				   GTK_WINDOW (state->dialog));
	gtk_widget_show (GTK_WIDGET (state->dialog));
}
