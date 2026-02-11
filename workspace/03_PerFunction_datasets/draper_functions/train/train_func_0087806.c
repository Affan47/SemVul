esma_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ESelectionModelArray *esma = E_SELECTION_MODEL_ARRAY (object);

	switch (property_id) {
	case PROP_CURSOR_ROW:
		g_value_set_int (value, esma->cursor_row);
		break;

	case PROP_CURSOR_COL:
		g_value_set_int (value, esma->cursor_col);
		break;
	}
}
