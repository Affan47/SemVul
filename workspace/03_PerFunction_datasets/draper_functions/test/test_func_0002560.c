sign_test_two_tool_update_sensitivity_cb (G_GNUC_UNUSED GtkWidget *dummy,
				      SignTestToolState *state)
{
        GnmValue *input_range;
 	gint w, h;


        input_range = gnm_expr_entry_parse_as_value
		(GNM_EXPR_ENTRY (state->base.input_entry),
		 state->base.sheet);
	if (input_range == NULL || input_range->type != VALUE_CELLRANGE) {
		gtk_label_set_text (GTK_LABEL (state->base.warning),
				    (state->base.input_entry_2 == NULL)
				    ? _("The input range is invalid.")
				    : _("The first input range is invalid."));
		gtk_widget_set_sensitive (state->base.ok_button, FALSE);
		value_release (input_range);
		return;
	} else {
		GnmRange r;
		range_init_rangeref (&r, &(input_range->v_range.cell));
		w = range_width (&r);
		h = range_height (&r);
		value_release (input_range);
	}


	if (state->base.input_entry_2 != NULL) {
		input_range = gnm_expr_entry_parse_as_value
			(GNM_EXPR_ENTRY (state->base.input_entry_2),
			 state->base.sheet);
		if (input_range == NULL || input_range->type != VALUE_CELLRANGE) {
			gtk_label_set_text (GTK_LABEL (state->base.warning),
					    _("The second input range is invalid."));
			gtk_widget_set_sensitive (state->base.ok_button, FALSE);
			value_release (input_range);
			return;
		} else {
			GnmRange r;
			range_init_rangeref (&r, &(input_range->v_range.cell));
			value_release (input_range);
			if (w != range_width (&r) ||
			    h != range_height (&r)) {
				gtk_label_set_text
					(GTK_LABEL (state->base.warning),
					 _("The input ranges do not have the same shape."));
				gtk_widget_set_sensitive
					(state->base.ok_button, FALSE);
			return;

			}
		}
	}

	if (sign_test_tool_update_common_sensitivity_cb (state)) {
		gtk_label_set_text (GTK_LABEL (state->base.warning), "");
		gtk_widget_set_sensitive (state->base.ok_button, TRUE);
	}
}
