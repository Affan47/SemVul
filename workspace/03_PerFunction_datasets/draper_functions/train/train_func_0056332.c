et_set_property (GObject *object,
                 guint property_id,
                 const GValue *value,
                 GParamSpec *pspec)
{
	ETree *tree = E_TREE (object);

	switch (property_id) {
	case PROP_LENGTH_THRESHOLD:
		tree->priv->length_threshold = g_value_get_int (value);
		if (tree->priv->item) {
			gnome_canvas_item_set (
				GNOME_CANVAS_ITEM (tree->priv->item),
				"length_threshold",
				tree->priv->length_threshold,
				NULL);
		}
		break;

	case PROP_HORIZONTAL_DRAW_GRID:
		tree->priv->horizontal_draw_grid = g_value_get_boolean (value);
		if (tree->priv->item) {
			gnome_canvas_item_set (
				GNOME_CANVAS_ITEM (tree->priv->item),
				"horizontal_draw_grid",
				tree->priv->horizontal_draw_grid,
				NULL);
		}
		break;

	case PROP_VERTICAL_DRAW_GRID:
		tree->priv->vertical_draw_grid = g_value_get_boolean (value);
		if (tree->priv->item) {
			gnome_canvas_item_set (
				GNOME_CANVAS_ITEM (tree->priv->item),
				"vertical_draw_grid",
				tree->priv->vertical_draw_grid,
				NULL);
		}
		break;

	case PROP_DRAW_FOCUS:
		tree->priv->draw_focus = g_value_get_boolean (value);
		if (tree->priv->item) {
			gnome_canvas_item_set (
				GNOME_CANVAS_ITEM (tree->priv->item),
				"drawfocus",
				tree->priv->draw_focus,
				NULL);
		}
		break;

	case PROP_UNIFORM_ROW_HEIGHT:
		tree->priv->uniform_row_height = g_value_get_boolean (value);
		if (tree->priv->item) {
			gnome_canvas_item_set (
				GNOME_CANVAS_ITEM (tree->priv->item),
				"uniform_row_height",
				tree->priv->uniform_row_height,
				NULL);
		}
		break;

	case PROP_ALWAYS_SEARCH:
		if (tree->priv->always_search == g_value_get_boolean (value))
			return;
		tree->priv->always_search = g_value_get_boolean (value);
		clear_current_search_col (tree);
		break;

	case PROP_HADJUSTMENT:
		if (tree->priv->table_canvas)
			g_object_set_property (
				G_OBJECT (tree->priv->table_canvas),
				"hadjustment", value);
		break;

	case PROP_VADJUSTMENT:
		if (tree->priv->table_canvas)
			g_object_set_property (
				G_OBJECT (tree->priv->table_canvas),
				"vadjustment", value);
		break;

	case PROP_HSCROLL_POLICY:
		if (tree->priv->table_canvas)
			g_object_set_property (
				G_OBJECT (tree->priv->table_canvas),
				"hscroll-policy", value);
		break;

	case PROP_VSCROLL_POLICY:
		if (tree->priv->table_canvas)
			g_object_set_property (
				G_OBJECT (tree->priv->table_canvas),
				"vscroll-policy", value);
		break;
	}
}
