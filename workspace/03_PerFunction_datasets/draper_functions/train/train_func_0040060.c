cb_gee_button_press_event (G_GNUC_UNUSED GtkEntry *entry,
			   G_GNUC_UNUSED GdkEventButton *event,
			   GnmExprEntry *gee)
{
	g_return_val_if_fail (IS_GNM_EXPR_ENTRY (gee), FALSE);

	if (gee->scg) {
		scg_rangesel_stop (gee->scg, FALSE);
		gnm_expr_entry_find_range (gee);
		g_signal_emit (G_OBJECT (gee), signals[CHANGED], 0);
	}

	return FALSE;
}
