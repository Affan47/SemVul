custom_list_get_value (GtkTreeModel *tree_model,
				   GtkTreeIter  *iter,
				   gint          column,
				   GValue       *value)
{
    CustomRecord  *record;
    CustomList    *custom_list;

    g_return_if_fail (CUSTOM_IS_LIST (tree_model));
    g_return_if_fail (iter != NULL);
    g_return_if_fail (column < CUSTOM_LIST(tree_model)->n_columns);

    g_value_init (value, CUSTOM_LIST(tree_model)->column_types[column]);

    custom_list = CUSTOM_LIST(tree_model);

    record = (CustomRecord*) iter->user_data;
    g_return_if_fail ( record != NULL );

    switch(column)
    {
	case CUSTOM_MODEL_COL_0:
	case CUSTOM_MODEL_COL_1:
	case CUSTOM_MODEL_COL_2:
	case CUSTOM_MODEL_COL_3:
	case CUSTOM_MODEL_COL_4:
	case CUSTOM_MODEL_COL_5:
	case CUSTOM_MODEL_COL_6:
	    g_value_set_string(value, record->visible_col[column]);
	    break;
	case CUSTOM_MODEL_BACKGROUND:
	    g_value_set_boxed(value, (gpointer) record->row_bg);
	    break;
	case CUSTOM_MODEL_SAVE_BACKGROUND:
	    g_value_set_boxed(value, (gpointer) record->row_bg_save);
	    break;
	case CUSTOM_MODEL_AMOUNT_COLOR:
	    g_value_set_string(value, record->amount_color);
	    break;
	case CUSTOM_MODEL_TEXT_COLOR:
	    g_value_set_boxed(value, (gpointer) record->text_color);
	    break;
	case CUSTOM_MODEL_TRANSACTION_ADDRESS:
	    g_value_set_pointer(value, record->transaction_pointer);
	    break;
	case CUSTOM_MODEL_WHAT_IS_LINE:
	    g_value_set_int(value, record->what_is_line);
	    break;
	case CUSTOM_MODEL_FONT:
	    g_value_set_string(value, record->font);
	    break;
	case CUSTOM_MODEL_TRANSACTION_LINE:
	    g_value_set_int(value, record->line_in_transaction);
	    break;
	case CUSTOM_MODEL_VISIBLE:
	    g_value_set_boolean(value, record->line_visible);
	    break;
	case CUSTOM_MODEL_CHECKBOX_VISIBLE:
	    g_value_set_boolean(value, record->checkbox_visible);
	    break;
	case CUSTOM_MODEL_CHECKBOX_VISIBLE_RECONCILE:
	    g_value_set_boolean(value, record->checkbox_visible_reconcile);
	    break;
	case CUSTOM_MODEL_CHECKBOX_ACTIVE:
	    g_value_set_boolean(value, record->checkbox_active);
	    break;
	default:
	    devel_debug ("Wrong value asked for CustomList");
    }
}
