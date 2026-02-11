e_table_item_print_page (EPrintable *ep,
                         GtkPrintContext *context,
                         gdouble width,
                         gdouble height,
                         gboolean quantize,
                         ETableItemPrintContext *itemcontext)
{
	ETableItem *eti = itemcontext->item;
	const gint rows = eti->rows;
	const gint cols = eti->cols;
	gdouble max_height;
	gint rows_printed = itemcontext->rows_printed;
	gint row, col, next_page = 0;
	gdouble yd = height;
	cairo_t *cr;
	gdouble *widths;

	cr = gtk_print_context_get_cairo_context (context);
	max_height = gtk_print_context_get_height (context);
	widths = e_table_item_calculate_print_widths (itemcontext->item->header, width);


	if (eti->horizontal_draw_grid) {
		gp_draw_rect (context, 0, yd, width, 1);
	}
	yd++;

	for (row = rows_printed; row < rows; row++) {
		gdouble xd = 1, row_height;
		row_height = eti_printed_row_height (eti, widths, context, row);

		if (quantize) {
			if (yd + row_height + 1 > max_height && row != rows_printed) {
				next_page = 1;
				break;
			}
		} else {
			if (yd > max_height) {
				next_page = 1;
				break;
			}
		}

		for (col = 0; col < cols; col++) {
			ECellView *ecell_view = eti->cell_views[col];

			cairo_save (cr);
			cairo_translate (cr, xd, yd);
			cairo_rectangle (cr, 0, 0, widths[col] - 1, row_height);
			cairo_clip (cr);

			e_cell_print (
				ecell_view, context,
				view_to_model_col (eti, col),
				col,
				row,
				widths[col] - 1,
				row_height + 2);

			cairo_restore (cr);

			xd += widths[col];
		}

	yd += row_height;
		if (eti->horizontal_draw_grid) {
			gp_draw_rect (context, 0, yd, width, 1);
		}
		yd++;
	}

	itemcontext->rows_printed = row;
	if (eti->vertical_draw_grid) {
		gdouble xd = 0;
		for (col = 0; col < cols; col++) {
			gp_draw_rect (context, xd, height, 1, yd - height);
			xd += widths[col];
		}
		gp_draw_rect (context, xd, height, 1, yd - height);
	}

	if (next_page)
		cairo_show_page (cr);

	g_free (widths);
}
