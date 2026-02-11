sheet_widget_button_user_config (SheetObject *so, SheetControl *sc)
{
	SheetWidgetButton *swb = GNM_SOW_BUTTON (so);
	WBCGtk  *wbcg = scg_wbcg (SHEET_CONTROL_GUI (sc));
	ButtonConfigState *state;
	GtkWidget *grid;
	GtkBuilder *gui;

	g_return_if_fail (swb != NULL);


	if (gnumeric_dialog_raise_if_exists (wbcg, SHEET_OBJECT_CONFIG_KEY))
		return;

	gui = gnm_gtk_builder_load ("so-button.ui", NULL, GO_CMD_CONTEXT (wbcg));
	if (!gui)
		return;
	state = g_new (ButtonConfigState, 1);
	state->swb = swb;
	state->wbcg = wbcg;
	state->sheet = sc_sheet	(sc);
	state->old_focus = NULL;
	state->old_label = g_strdup (swb->label);
	state->dialog = go_gtk_builder_get_widget (gui, "SO-Button");

	grid = go_gtk_builder_get_widget (gui, "main-grid");

	state->expression = gnm_expr_entry_new (wbcg, TRUE);
	gnm_expr_entry_set_flags (state->expression,
		GNM_EE_FORCE_ABS_REF | GNM_EE_SHEET_OPTIONAL | GNM_EE_SINGLE_RANGE,
		GNM_EE_MASK);
	gnm_expr_entry_load_from_dep (state->expression, &swb->dep);
	go_atk_setup_label (go_gtk_builder_get_widget (gui, "label_linkto"),
			     GTK_WIDGET (state->expression));
	gtk_grid_attach (GTK_GRID (grid),
	                 GTK_WIDGET (state->expression), 1, 0, 1, 1);
	gtk_widget_show (GTK_WIDGET (state->expression));

	state->label = go_gtk_builder_get_widget (gui, "label_entry");
	gtk_entry_set_text (GTK_ENTRY (state->label), swb->label);
	gtk_editable_select_region (GTK_EDITABLE(state->label), 0, -1);
	gnumeric_editable_enters (GTK_WINDOW (state->dialog),
				  GTK_WIDGET (state->expression));
	gnumeric_editable_enters (GTK_WINDOW (state->dialog),
				  GTK_WIDGET (state->label));

	g_signal_connect (G_OBJECT (state->label),
		"changed",
		G_CALLBACK (cb_button_label_changed), state);
	g_signal_connect (G_OBJECT (go_gtk_builder_get_widget (gui, "ok_button")),
		"clicked",
		G_CALLBACK (cb_button_config_ok_clicked), state);
	g_signal_connect (G_OBJECT (go_gtk_builder_get_widget (gui, "cancel_button")),
		"clicked",
		G_CALLBACK (cb_button_config_cancel_clicked), state);

	gnumeric_init_help_button (
		go_gtk_builder_get_widget (gui, "help_button"),
		GNUMERIC_HELP_LINK_SO_BUTTON);

	gnumeric_keyed_dialog (state->wbcg, GTK_WINDOW (state->dialog),
			       SHEET_OBJECT_CONFIG_KEY);

	wbc_gtk_attach_guru (state->wbcg, state->dialog);
	g_object_set_data_full (G_OBJECT (state->dialog),
		"state", state, (GDestroyNotify) cb_button_config_destroy);


	g_signal_connect (G_OBJECT (state->dialog), "set-focus",
		G_CALLBACK (cb_button_set_focus), state);
	g_object_unref (gui);

	gtk_widget_show (state->dialog);
}
