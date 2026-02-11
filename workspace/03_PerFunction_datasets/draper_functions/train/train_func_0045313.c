gtk_term_button_release (GtkWidget *widget, GdkEventButton *event)
{
	GtkTerm *	term;

	g_return_val_if_fail (widget != NULL,FALSE);
	g_return_val_if_fail (GTK_IS_TERM (widget),FALSE);
	g_return_val_if_fail (event!=NULL,FALSE);

	term = GTK_TERM (widget);

	switch (event->button) {
		case 1:
			term->selecting = 0;
			gtk_term_redraw_current(term);
			gtk_term_draw_caret(term,1);
			break;
		case 4:
			gtk_term_adjustment_safe_set_value(term, term->v_adj->value-term->theight+1);
			break;
		case 5:
			gtk_term_adjustment_safe_set_value(term, (gfloat)MIN(term->top+term->theight-1,e_get_length(term->a)-term->theight));
			break;
	}
	return FALSE;
}
