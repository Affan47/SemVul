gnucash_sheet_col_max_width (GnucashSheet *sheet, gint virt_col, gint cell_col)
{
    int virt_row;
    int cell_row;
    int max = 0;
    int width;
    SheetBlock *block;
    SheetBlockStyle *style;
    PangoLayout *layout = gtk_widget_create_pango_layout (GTK_WIDGET (sheet), "");

    g_return_val_if_fail (virt_col >= 0, 0);
    g_return_val_if_fail (virt_col < sheet->num_virt_cols, 0);
    g_return_val_if_fail (cell_col >= 0, 0);

    for (virt_row = 0; virt_row < sheet->num_virt_rows ; virt_row++)
    {
        VirtualCellLocation vcell_loc = { virt_row, virt_col };

        block = gnucash_sheet_get_block (sheet, vcell_loc);
        style = block->style;

        if (!style)
            continue;

        if (cell_col < style->ncols)
            for (cell_row = 0; cell_row < style->nrows; cell_row++)
            {
                VirtualLocation virt_loc;
                const char *text;

                virt_loc.vcell_loc = vcell_loc;
                virt_loc.phys_row_offset = cell_row;
                virt_loc.phys_col_offset = cell_col;

                if (virt_row == 0)
                {
                    text = gnc_table_get_label
                           (sheet->table, virt_loc);
                }
                else
                {
                    text = gnc_table_get_entry
                           (sheet->table, virt_loc);
                }

                pango_layout_set_text (layout, text, strlen (text));
                pango_layout_get_pixel_size (layout, &width, NULL);

                width += 2 * CELL_HPADDING;

                max = MAX (max, width);
            }
    }

    g_object_unref (layout);

    return max;
}
