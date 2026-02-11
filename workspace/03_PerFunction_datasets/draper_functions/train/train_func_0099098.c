validation_rebuild_validation (FormatState *state)
{
	ValidationType	type;

	if (!state->enable_edit)
		return;

	state->validation.changed = FALSE;
	type = gtk_combo_box_get_active (
		state->validation.constraint_type);

	if (type != GNM_VALIDATION_TYPE_ANY) {
		ValidationStyle style = gtk_combo_box_get_active (state->validation.error.action);
		ValidationOp    op    = gtk_combo_box_get_active (state->validation.op);
		char *title = gtk_editable_get_chars (GTK_EDITABLE (state->validation.error.title), 0, -1);
		char *msg   = gnumeric_textview_get_text (state->validation.error.msg);
		GnmExprTop const *texpr0 =
			validation_entry_to_expr (state->sheet,
						  state->validation.expr0.entry);
		GnmExprTop const *texpr1 = NULL;

		if (texpr0 != NULL) {
			if (type == GNM_VALIDATION_TYPE_CUSTOM || type == GNM_VALIDATION_TYPE_IN_LIST) {
				state->validation.valid = 1;
				op = GNM_VALIDATION_OP_NONE;
			} else if (op == GNM_VALIDATION_OP_BETWEEN || op == GNM_VALIDATION_OP_NOT_BETWEEN) {
				texpr1 = validation_entry_to_expr (state->sheet,
								   state->validation.expr1.entry);
				if (texpr1 != NULL)
					state->validation.valid = 2;
				else {
					state->validation.valid = -2;
					gnm_expr_top_unref (texpr0);
				}
			} else
				state->validation.valid = 1;
		} else
			state->validation.valid = -1;

		if (state->validation.valid > 0) {
			gboolean allow_blank = gtk_toggle_button_get_active (state->validation.allow_blank);
			gboolean use_dropdown = gtk_toggle_button_get_active (state->validation.use_dropdown);
			gnm_style_set_validation
				(state->result,
				 gnm_validation_new
				 (style, type, op,
				  state->sheet,
				  title, msg,
				  texpr0,
				  texpr1,
				  allow_blank,
				  use_dropdown));
		}

		g_free (msg);
		g_free (title);
	} else
		gnm_style_set_validation (state->result, NULL);
	fmt_dialog_changed (state);
}
