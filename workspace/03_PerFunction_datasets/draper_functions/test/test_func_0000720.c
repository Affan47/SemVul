map_op (AutoFilterState *state, GnmFilterOp *op,
	char const *op_widget, char const *val_widget)
{
	int i;
	GtkWidget *w = go_gtk_builder_get_widget (state->gui, val_widget);
	char const *txt = gtk_entry_get_text (GTK_ENTRY (w));
	GnmValue *v = NULL;

	*op = GNM_FILTER_UNUSED;
	if (txt == NULL || *txt == '\0')
		return NULL;

	w = go_gtk_builder_get_widget (state->gui, op_widget);
	i = gtk_combo_box_get_active (GTK_COMBO_BOX (w));
	switch (i) {
	case 0: return NULL;
	case 1: *op = GNM_FILTER_OP_EQUAL;	break;
	case 2: *op = GNM_FILTER_OP_NOT_EQUAL;	break;
	case 3: *op = GNM_FILTER_OP_GT;		break;
	case 4: *op = GNM_FILTER_OP_GTE;	break;
	case 5: *op = GNM_FILTER_OP_LT;		break;
	case 6: *op = GNM_FILTER_OP_LTE;	break;

	case 7:
	case 8: *op = (i == 8) ? GNM_FILTER_OP_NOT_EQUAL : GNM_FILTER_OP_EQUAL;
		v = value_new_string_nocopy (g_strconcat (txt, "*", NULL));
		break;

	case 9:
	case 10: *op = (i == 10) ? GNM_FILTER_OP_NOT_EQUAL : GNM_FILTER_OP_EQUAL;
		v = value_new_string_nocopy (g_strconcat ("*", txt, NULL));
		break;

	case 11:
	case 12: *op = (i == 12) ? GNM_FILTER_OP_NOT_EQUAL : GNM_FILTER_OP_EQUAL;
		v = value_new_string_nocopy (g_strconcat ("*", txt, "*", NULL));
		break;
	default :
		g_warning ("huh?");
		return NULL;
	}

	if (v == NULL) {
		Workbook *wb = wb_control_get_workbook (WORKBOOK_CONTROL (state->wbcg));
		v = format_match (txt, NULL, workbook_date_conv (wb));
	}
	if (v == NULL)
		v = value_new_string (txt);

	return v;
}
