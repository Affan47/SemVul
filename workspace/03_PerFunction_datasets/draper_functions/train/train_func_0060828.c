ecv_draw (ECellView *ecell_view,
          cairo_t *cr,
          gint model_col,
          gint view_col,
          gint row,
          ECellFlags flags,
          gint x1,
          gint y1,
          gint x2,
          gint y2)
{
	ECellVboxView *vbox_view = (ECellVboxView *) ecell_view;

	gint subcell_offset = 0;
	gint i;

	for (i = 0; i < vbox_view->subcell_view_count; i++) {


		gint height;

		height = e_cell_height (
			vbox_view->subcell_views[i],
			vbox_view->model_cols[i], view_col, row);
		e_cell_draw (
			vbox_view->subcell_views[i], cr,
			vbox_view->model_cols[i], view_col, row, flags,
			x1, y1 + subcell_offset, x2,
			y1 + subcell_offset + height);

		subcell_offset += e_cell_height (
			vbox_view->subcell_views[i],
			vbox_view->model_cols[i], view_col, row);
	}
}
